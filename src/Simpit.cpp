#include "Simpit.h"
#include "COBS.h"
#include "CheckSum.h"
#include "CoreSimpitMessageTypes.h"
#include "CoreSimpitMessageTypeIds.h"
#include "SimpitMacros.h"

#define SIMPIT_VERSION "3.0.1.rettoph"

SIMPIT_DECLARE_OUTGOING_TYPE(EchoRequest, SIMPIT_CORE_OUTGOING_ECHO_REQUEST_ID);
SIMPIT_DECLARE_OUTGOING_TYPE(EchoResponse, SIMPIT_CORE_OUTGOING_ECHO_RESPONSE_ID);
SIMPIT_DECLARE_OUTGOING_TYPE(CloseSerialPort, SIMPIT_CORE_OUTGOING_CLOSE_SERIAL_PORT_ID);
SIMPIT_DECLARE_OUTGOING_TYPE(RegisterHandler, SIMPIT_CORE_OUTGOING_REGISTER_HANDLER_ID);
SIMPIT_DECLARE_OUTGOING_TYPE(DeregisterHandler, SIMPIT_CORE_OUTGOING_DEREGISTER_HANDLER_ID);
SIMPIT_DECLARE_OUTGOING_TYPE(CustomLog, SIMPIT_CORE_OUTGOING_CUSTOM_LOG_ID);
SIMPIT_DECLARE_OUTGOING_TYPE(Request, SIMPIT_CORE_OUTGOING_REQUEST_MESSAGE_ID);

SIMPIT_DECLARE_INCOMING_TYPE(EchoRequest, SIMPIT_CORE_INCOMING_ECHO_REQUEST_ID);

Simpit::Simpit(byte incomingMessageHandlerCapacity, Stream &serial) : 
    _messageTypes(SimpitMessageTypeProvider(incomingMessageHandlerCapacity)),
    _serial(SerialPort(serial))
{
}

bool Simpit::Init(byte response)
{
    // Empty the serial buffer
    _serial.Clear();

    // Broadcast a SYN request
    Synchronisation synchronisation = Synchronisation();
    synchronisation.Type = SynchronisationMessageTypeEnum::SYN;
    synchronisation.Version = FixedString(SIMPIT_VERSION);
    _serial.TryWriteOutgoing(SIMPIT_CORE_OUTGOING_SYNCHRONISATION_ID, &synchronisation, sizeof(Synchronisation));

    // Wait for reply - if non in 1 sec, return false
    byte count = 0;
    while(_serial.TryReadIncoming(&_buffer) == false)
    {
        count += 1;
        delay(100);

        if(count > 10)
        {
            return false;
        }
    }

    byte id;
    if(_buffer.TryReadByte(id) == false)
    { // No data recieved?
        return false;
    }

    if(id != SIMPIT_CORE_INCOMING_HANDSHAKE_MESSAGE_ID)
    { // Invalid Handshake packet
        return false;
    }

    Handshake handshake = Handshake();
    _buffer.TryReadBytes(sizeof(Handshake), &handshake);
    _buffer.Clear();

    if(handshake.HandshakeType != 0x01)
    { // Not a SYNACK response
        return false;
    }
    
    if(handshake.Payload != response)
    { // Incorrect handshake response
        return false;
    }

    synchronisation.Type = SynchronisationMessageTypeEnum::ACK;
    _serial.TryWriteOutgoing(SIMPIT_CORE_OUTGOING_SYNCHRONISATION_ID, &synchronisation, sizeof(Synchronisation));

    return true;
}

void Simpit::Update()
{
    int incoming = this->ReadIncoming();
}

int Simpit::ReadIncoming()
{
    int count = 0;
    while(_serial.TryReadIncoming(&_buffer))
    {
        byte id;
        if(_buffer.TryReadByte(id) == false)
        { // Invalid message
            _buffer.Clear();
            continue;
        }

        byte index = 0;
        IncomingSimpitMessageType* incoming;
        while(_messageTypes.TryGetIncomingMessageType(id, *&incoming, index) == true)
        { // Unknown message type id
            if(incoming->TryPublish(this, _buffer) == false)
            {
                break;
            }

            count++;
        }

        _buffer.Clear();
        
    }

    return count;
}

void Simpit::Log(String value)
{
    this->Log(value, CustomLogFlags::PrintToScreen);
}

void Simpit::Log(String value, CustomLogFlags flags)
{
    CustomLog log = CustomLog();
    log.Flags = flags;
    log.Value = FixedString(value);

    this->WriteOutgoing(log);
}

void Simpit::SubscribeIncoming(RegisterHandler subscriptions)
{
    this->WriteOutgoing(subscriptions);
}

void Simpit::UnsubscribeIncoming(DeregisterHandler unsubscriptions)
{
    this->WriteOutgoing(unsubscriptions);
}