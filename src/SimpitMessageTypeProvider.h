#ifndef SimpitMessageTypeProvider_h
#define SimpitMessageTypeProvider_h

#include "SimpitMessageType.h"

class SimpitMessageTypeProvider
{
private:
    byte _incomingCount;
    IncomingSimpitMessageType *_incoming;

public:
    SimpitMessageTypeProvider(byte incomingCapacity);
    ~SimpitMessageTypeProvider();

    bool TryGetIncomingMessageType(byte id, IncomingSimpitMessageType *&messageType);

    template<typename T> bool TryRegisterIncoming(void(*handler)(void*, T*))
    {
        _incoming[_incomingCount++] = GenericIncomingSimpitMessageType<T>(GenericIncomingSimpitMessageType<T>::MessageTypeId, handler);

        return true;
    }
};

#endif