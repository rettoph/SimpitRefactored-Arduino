#include "Simpit.h"
#include "COBS.h"
#include "CheckSum.h"

Simpit::Simpit(BaseSimpitMessageType **types, uint16_t typeCount)
{
    _types = types;
    _typeCount = typeCount; 
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

void Simpit::ReadIncoming(SimpitStream incoming)
{
    if(COBS::TryDecode(incoming) == false)
    {
        return;
    }

    if(CheckSum::ValidateCheckSum(incoming) == false)
    {
        return;
    }

    byte id;
    if(incoming.TryReadByte(id) == false)
    {
        return;
    }

    BaseSimpitMessageType* messageType;
    if(this->TryGetMessageType(id, *&messageType) == false)
    {
        return; // TODO: Some sort of error handling here
    }

    messageType->Publish(incoming);
}
