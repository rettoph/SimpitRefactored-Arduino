#include "Simpit.h"
#include "COBS.h"
#include "CheckSum.h"
#include "CoreSimpitMessageTypes.h"

#define SIMPIT_VERSION "2.4.0"

Simpit::Simpit(BaseSimpitMessageType **types, uint16_t typeCount, Stream &serial)
{
    _types = types;
    _typeCount = typeCount; 
    _serial = new SerialPort(serial);
}

bool Simpit::Init(byte response)
{
    // Empty the serial buffer
    _serial->Clear();

    // Broadcast a SYN request
    Synchronisation synchronisation = Synchronisation();
    synchronisation.Type = SynchronisationMessageTypeEnum::SYN;
    synchronisation.Version = FixedString(SIMPIT_VERSION);
    _serial->TryWriteOutgoing(Synchronisation::MessageTypeId, &synchronisation, sizeof(Synchronisation));

    // Wait for reply - if non in 1 sec, return false
    byte count = 0;
    while(_serial->TryReadIncoming(_buffer) == false)
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

    if(id != Handshake::MessageTypeId)
    { // Invalid Handshake packet
        return false;
    }

    Handshake handshake = Handshake();
    _buffer.TryReadBytes(sizeof(Handshake), &handshake);

    if(handshake.HandshakeType != 0x01)
    { // Not a SYNACK response
        return false;
    }
    
    if(handshake.Payload != response)
    { // Incorrect handshake response
        return false;
    }

    synchronisation.Type = SynchronisationMessageTypeEnum::ACK;
    _serial->TryWriteOutgoing(Synchronisation::MessageTypeId, &synchronisation, sizeof(Synchronisation));

    return true;
}

bool Simpit::TryGetMessageType(byte id, BaseSimpitMessageType *&messageType, SimpitMessageTypeEnum type)
{
    for(int i = 0; i < _typeCount; i++)
    {
        if(_types[i]->Id != id)
        {
            continue;
        }

        if(_types[i]->Type != type)
        {
            continue;;
        }

        messageType = *&_types[i];
        return true;
    }

    return false;
}

int Simpit::ReadIncoming()
{
    int incoming = 0;
    while(_serial->TryReadIncoming(_buffer))
    {
        byte id;
        if(_buffer.TryReadByte(id) == false)
        { // Invalid message
            continue;
        }

        BaseSimpitMessageType* messageType;
        if(this->TryGetMessageType(id, *&messageType, SimpitMessageTypeEnum::Incoming) == false)
        { // Unknown message type id
            continue; // TODO: Some sort of error handling here
        }

        BaseIncomingSimpitMessageType* casted = (BaseIncomingSimpitMessageType*)messageType;
        casted->Publish(_buffer);
        incoming++;
    }

    _buffer.Clear();
    return incoming;
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