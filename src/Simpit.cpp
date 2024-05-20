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

bool Simpit::Init()
{
    // Empty the serial buffer
    _serial->Clear();

    Synchronisation synchronisation = Synchronisation();
    synchronisation.Type = SynchronisationMessageTypeEnum::SYN;
    synchronisation.Version = FixedString(SIMPIT_VERSION);

    _serial->TryWriteOutgoing(Synchronisation::MessageTypeId, &synchronisation, sizeof(Synchronisation));

    return false;
}

bool Simpit::TryGetMessageType(byte id, BaseSimpitMessageType *&messageType)
{
    for(int i = 0; i < _typeCount; i++)
    {
        if(_types[i]->Id != id)
        {
            continue;
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
        if(this->TryGetMessageType(id, *&messageType) == false)
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
