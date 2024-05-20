#ifndef SimpitMessageTypeProvider_h
#define SimpitMessageTypeProvider_h

#include "SimpitMessageType.h"

class SimpitMessageTypeProvider
{
private:
    uint16_t _capacity;
    uint16_t _count;
    BaseSimpitMessageType **_items;

public:
    SimpitMessageTypeProvider(uint16_t capacity);
    ~SimpitMessageTypeProvider();

    bool TryGetMessageType(byte id, SimpitMessageTypeEnum type, BaseSimpitMessageType *&messageType);

    template<typename T> bool TryRegisterIncoming()
    {
        if(_count == _capacity)
        {
            return false;
        }

        BaseSimpitMessageType* messageType;
        if(this->TryGetMessageType(IncomingSimpitMessageType<T>::MessageTypeId, SimpitMessageTypeEnum::Incoming, messageType) == true)
        {
            return false;
        }

        _items[_count++] = new IncomingSimpitMessageType<T>(IncomingSimpitMessageType<T>::MessageTypeId, SimpitMessageTypeEnum::Incoming);
        return true;
    }

    template<typename T> bool TryRegisterOutgoing()
    {
        if(_count == _capacity)
        {
            return false;
        }

        BaseSimpitMessageType* messageType;
        if(this->TryGetMessageType(OutgoingSimpitMessageType<T>::MessageTypeId, SimpitMessageTypeEnum::Outgoing, messageType) == true)
        {
            return false;
        }

        _items[_count++] = new OutgoingSimpitMessageType<T>(OutgoingSimpitMessageType<T>::MessageTypeId, SimpitMessageTypeEnum::Outgoing);
        return true;
    }

    void Trim();
};

#endif