#ifndef SimpitMessageTypeProvider_h
#define SimpitMessageTypeProvider_h

#include "SimpitMessageType.h"

class SimpitMessageTypeProvider
{
private:
    byte _incomingCount;
    IncomingSimpitMessageType **_incoming;

    byte _outgoingCount;
    OutgoingSimpitMessageType **_outgoing;

public:
    SimpitMessageTypeProvider(byte incomingCapacity, byte outgoingCapacity);
    ~SimpitMessageTypeProvider();

    bool TryGetIncomingMessageType(byte id, IncomingSimpitMessageType *&messageType);

    bool TryGetOutgoingMessageType(byte id, OutgoingSimpitMessageType *&messageType);

    int PublishIncoming(void* sender, SimpitStream simpit);

    template<typename T> bool TryRegisterIncoming(void(*handler)(void*, T*))
    {
        GenericIncomingSimpitMessageType<T>* type = new GenericIncomingSimpitMessageType<T>(GenericIncomingSimpitMessageType<T>::MessageTypeId, handler);
        _incoming[_incomingCount++] = (IncomingSimpitMessageType*)type;

        return true;
    }

    template<typename T> bool TryRegisterOutgoing()
    {
        GenericOutgoingSimpitMessageType<T>* type = new GenericOutgoingSimpitMessageType<T>(GenericOutgoingSimpitMessageType<T>::MessageTypeId);
        _outgoing[_outgoingCount++] = (OutgoingSimpitMessageType*)type;

        return true;
    }
};

#endif