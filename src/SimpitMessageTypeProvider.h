#ifndef SimpitMessageTypeProvider_h
#define SimpitMessageTypeProvider_h

#include "SimpitMessageType.h"

#define SimpitMessageTypeProvider_Capacity 512

class SimpitMessageTypeProvider
{
private:
    uint16_t _count;
    const BaseSimpitMessageType PROGMEM *_items[SimpitMessageTypeProvider_Capacity];
    byte PROGMEM _sizes[SimpitMessageTypeProvider_Capacity];

public:
    SimpitMessageTypeProvider(uint16_t capacity);
    ~SimpitMessageTypeProvider();

    bool TryGetMessageType(byte id, SimpitMessageTypeEnum type, const BaseSimpitMessageType *&messageType);

    template<typename T> bool TryRegisterIncoming()
    {
        if(_count == SimpitMessageTypeProvider_Capacity)
        {
            return false;
        }

        const BaseSimpitMessageType *messageType;
        if(this->TryGetMessageType(IncomingSimpitMessageType<T>::MessageTypeId, SimpitMessageTypeEnum::Incoming, messageType) == true)
        {
            return false;
        }

        _items[_count++] = &IncomingSimpitMessageType<T>::Instance;

        return true;
    }

    template<typename T> bool TryRegisterOutgoing()
    {
        if(_count == SimpitMessageTypeProvider_Capacity)
        {
            return false;
        }

        const BaseSimpitMessageType *messageType;
        if(this->TryGetMessageType(OutgoingSimpitMessageType<T>::MessageTypeId, SimpitMessageTypeEnum::Outgoing, messageType) == true)
        {
            return false;
        }

        _items[_count++] = &OutgoingSimpitMessageType<T>::Instance;

        return true;
    }
};

#endif