#ifndef SimpitMessageTypeProvider_h
#define SimpitMessageTypeProvider_h

#include "SimpitMessageType.h"

class SimpitMessageTypeProvider
{
private:
    byte _incomingCount;
    IncomingSimpitMessageType **_incoming;

public:
    SimpitMessageTypeProvider(byte incomingCapacity);
    ~SimpitMessageTypeProvider();

    bool TryGetIncomingMessageType(byte id, IncomingSimpitMessageType *&messageType);

    template<typename T> bool TryRegisterIncoming(void(*handler)(void*, T*))
    {
        GenericIncomingSimpitMessageType<T>* type = new GenericIncomingSimpitMessageType<T>(GenericIncomingSimpitMessageType<T>::MessageTypeId, handler);
        _incoming[_incomingCount++] = (IncomingSimpitMessageType*)type;

        return true;
    }
};

#endif