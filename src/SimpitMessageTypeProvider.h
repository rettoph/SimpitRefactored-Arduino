#ifndef SimpitMessageTypeProvider_h
#define SimpitMessageTypeProvider_h

#include "SimpitMessageType.h"

#define SimpitMessageTypeProvider_BufferIncrement 10

class SimpitMessageTypeProvider
{
private:
    uint16_t _incomingAlloc;
    byte _incomingCount;
    IncomingSimpitMessageType **_incoming;

    uint16_t _outgoingAlloc;
    byte _outgoingCount;
    OutgoingSimpitMessageType **_outgoing;

public:
    SimpitMessageTypeProvider();
    ~SimpitMessageTypeProvider();

    bool TryGetIncomingMessageType(byte id, IncomingSimpitMessageType *&messageType);

    bool TryGetOutgoingMessageType(byte id, OutgoingSimpitMessageType *&messageType);

    int PublishIncoming(void* sender);

    template<typename T> bool TryRegisterIncoming(void(*handler)(void*, T*))
    {
        if(_incomingCount > 0 && _incomingCount % SimpitMessageTypeProvider_BufferIncrement == 0)
        { // Time to resize the incoming buffer
            IncomingSimpitMessageType** newIncoming = (IncomingSimpitMessageType**)malloc(sizeof(IncomingSimpitMessageType**) * (_incomingCount + SimpitMessageTypeProvider_BufferIncrement));
            for(int i=0; i<_incomingCount; i++)
            {
                newIncoming[i] = _incoming[i];
            }

            free(_incoming);
            _incoming = newIncoming;
        }

        GenericIncomingSimpitMessageType<T>* type = new GenericIncomingSimpitMessageType<T>(GenericIncomingSimpitMessageType<T>::MessageTypeId, handler);
        _incoming[_incomingCount++] = (IncomingSimpitMessageType*)type;
        _incomingAlloc += sizeof(GenericIncomingSimpitMessageType<T>);

        return true;
    }

    template<typename T> bool TryRegisterOutgoing(bool(*delta)(T, T))
    {
        if(_outgoingCount > 0 && _outgoingCount % SimpitMessageTypeProvider_BufferIncrement == 0)
        { // Time to resize the outgoing buffer
            OutgoingSimpitMessageType** newOutgoing = (OutgoingSimpitMessageType**)malloc(sizeof(OutgoingSimpitMessageType**) * (_outgoingCount + SimpitMessageTypeProvider_BufferIncrement));
            for(int i=0; i<_outgoingCount; i++)
            {
                newOutgoing[i] = _outgoing[i];
            }

            free(_outgoing);
            _outgoing = newOutgoing;
        }

        GenericOutgoingSimpitMessageType<T>* type = new GenericOutgoingSimpitMessageType<T>(GenericOutgoingSimpitMessageType<T>::MessageTypeId, delta);
        _outgoing[_outgoingCount++] = (OutgoingSimpitMessageType*)type;
        _outgoingAlloc += sizeof(GenericOutgoingSimpitMessageType<T>);

        return true;
    }

    uint16_t GetIncomingAlloc() { return _incomingAlloc; }
    uint16_t GetOutgoingAlloc() { return _outgoingAlloc; }
};

#endif