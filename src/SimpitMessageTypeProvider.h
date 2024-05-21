#ifndef SimpitMessageTypeProvider_h
#define SimpitMessageTypeProvider_h

#include "SimpitMessageType.h"

#define SimpitMessageTypeProvider_BufferIncrement 10

class SimpitMessageTypeProvider
{
private:
    byte _incomingCount;
    IncomingSimpitMessageType **_incoming;

    byte _outgoingCount;
    OutgoingSimpitMessageType **_outgoing;

public:
    SimpitMessageTypeProvider();
    ~SimpitMessageTypeProvider();

    bool TryGetIncomingMessageType(byte id, IncomingSimpitMessageType *&messageType);

    bool TryGetOutgoingMessageType(byte id, OutgoingSimpitMessageType *&messageType);

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

        return true;
    }

    template<typename T> bool TryRegisterOutgoing()
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

        GenericOutgoingSimpitMessageType<T>* type = new GenericOutgoingSimpitMessageType<T>(GenericOutgoingSimpitMessageType<T>::MessageTypeId);
        _outgoing[_outgoingCount++] = (OutgoingSimpitMessageType*)type;

        return true;
    }
};

#endif