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
    SimpitStream *buffer;
    while(_serial->TryReadIncoming(buffer) == false)
    {
        count += 1;
        delay(100);

        if(count > 10)
        {
            return false;
        }
    }

    byte id;
    if(buffer->TryReadByte(id) == false)
    { // No data recieved?
        return false;
    }

    if(id != SIMPIT_CORE_INCOMING_HANDSHAKE_MESSAGE_ID)
    { // Invalid Handshake packet
        return false;
    }

    Handshake handshake = Handshake();
    buffer->TryReadBytes(sizeof(Handshake), &handshake);

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

    int totalAlloc = sizeof(this) + _messageTypes->GetSizeInBytes();
    this->Log("Runtime Alloc: " + String(totalAlloc), CustomLogFlags::Verbose);

    this->Log("Registered Incoming: " + String(_messageTypes->GetIncomingCount()), CustomLogFlags::Verbose);
    this->Log("Registered Outgoing: " + String(_messageTypes->GetOutgoingCount()), CustomLogFlags::Verbose);

    return true;
}

void Simpit::Update()
{
    int incoming = this->ReadIncoming();
    int published = _messageTypes->PublishIncoming(this);

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
    SimpitStream *buffer;
    while(_serial->TryReadIncoming(buffer))
    {
        byte id;
        if(buffer->TryReadByte(id) == false)
        { // Invalid message
            continue;
        }

        IncomingSimpitMessageType* incoming;
        if(_messageTypes->TryGetIncomingMessageType(id, *&incoming) == false)
        { // Unknown message type id
            this->Log("Unknown message: " + String(id));
            continue;
        }

        incoming->SetLatest(*buffer);
        count++;
    }

    _reading = false;

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