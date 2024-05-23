#include "Simpit.h"
#include "COBS.h"
#include "CheckSum.h"
#include "CoreSimpitMessageTypes.h"
#include "CoreSimpitMessageTypeIds.h"

#define SIMPIT_VERSION "2.4.0"

Simpit::Simpit(SimpitMessageTypeProvider *messageTypes, Stream &serial)
{
    _messageTypes = messageTypes;
    _serial = new SerialPort(serial);
    _register = RegisterHandler();
    _deregister = DeregisterHandler();
    _buffer = SimpitStream();

    // Ensure empty on startup
    memset(&_register, 0x0, sizeof(RegisterHandler));
    memset(&_deregister, 0x0, sizeof(RegisterHandler));
}

bool Simpit::Init(byte response)
{
    // Empty the serial buffer
    _serial->Clear();

    // Broadcast a SYN request
    Synchronisation synchronisation = Synchronisation();
    synchronisation.Type = SynchronisationMessageTypeEnum::SYN;
    synchronisation.Version = FixedString(SIMPIT_VERSION);
    _serial->TryWriteOutgoing(SIMPIT_CORE_OUTGOING_SYNCHRONISATION_ID, &synchronisation, sizeof(Synchronisation));

    // Wait for reply - if non in 1 sec, return false
    byte count = 0;
    while(_serial->TryReadIncoming(&_buffer) == false)
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
    _serial->TryWriteOutgoing(SIMPIT_CORE_OUTGOING_SYNCHRONISATION_ID, &synchronisation, sizeof(Synchronisation));

    return true;
}

void Simpit::Update()
{
    int incoming = this->ReadIncoming();
    int published = this->PublishIncoming();

    if(incoming != published)
    {
        // TODO: Some sort of error handling
    }

    if(_register.MessageTypeIds[0] != 0x0)
    {
        this->WriteOutgoing(_register);
        memset(&_register, 0x0, sizeof(RegisterHandler));
    }

    if(_deregister.MessageTypeIds[0] != 0x0)
    {
        this->WriteOutgoing(_deregister);
        memset(&_deregister, 0x0, sizeof(DeregisterHandler));
    }
}

int Simpit::ReadIncoming()
{
    _reading = true;

    int count = 0;
    while(_serial->TryReadIncoming(&_buffer))
    {
        byte id;
        if(_buffer.TryReadByte(id) == false)
        { // Invalid message
            _buffer.Clear();
            continue;
        }

        IncomingSimpitMessageType* incoming;
        if(_messageTypes->TryGetIncomingMessageType(id, *&incoming) == false)
        { // Unknown message type id
            this->Log("Unknown message: " + String(id) + " of size: " + String(_buffer.Length()));
            _buffer.Clear();
            continue;
        }

        incoming->SetLatest(_buffer);
        _buffer.Clear();
        count++;
    }

    _reading = false;

    return count;
}

int Simpit::PublishIncoming()
{
    _messageTypes->PublishIncoming(this);
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