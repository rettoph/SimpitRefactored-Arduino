#include "SimpitMessageTypeProvider.h"

SimpitMessageTypeProvider::SimpitMessageTypeProvider(uint16_t capacity)
{
    _count = 0;
}

bool SimpitMessageTypeProvider::TryGetMessageType(byte id, SimpitMessageTypeEnum type, const BaseSimpitMessageType *&messageType)
{
    for(int i = 0; i < _count; i++)
    {
        messageType = _items[i];

        if(messageType->Id != id)
        {
            continue;
        }

        if(messageType->Type != type)
        {
            continue;;
        }

        return true;
    }

    return false;
}