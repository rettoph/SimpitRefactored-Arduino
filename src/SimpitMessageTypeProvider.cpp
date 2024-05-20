#include "SimpitMessageTypeProvider.h"

SimpitMessageTypeProvider::SimpitMessageTypeProvider(uint16_t capacity)
{
    _capacity = capacity;
    _count = 0;
    _items = (BaseSimpitMessageType**)malloc(_capacity * sizeof(BaseSimpitMessageType*));
}

bool SimpitMessageTypeProvider::TryGetMessageType(byte id, SimpitMessageTypeEnum type, BaseSimpitMessageType *&messageType)
{
    for(int i = 0; i < _count; i++)
    {
        if(_items[i]->Id != id)
        {
            continue;
        }

        if(_items[i]->Type != type)
        {
            continue;;
        }

        messageType = *&_items[i];
        return true;
    }

    return false;
}

void SimpitMessageTypeProvider::Trim()
{
    BaseSimpitMessageType** items = (BaseSimpitMessageType**)malloc(_count * sizeof(BaseSimpitMessageType*));
    for(int i = 0; i < _count; i++)
    {
        items[i] = _items[i];
    }

    free(_items);
    _items = items;
}