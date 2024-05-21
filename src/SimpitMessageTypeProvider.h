#ifndef SimpitMessageTypeProvider_h
#define SimpitMessageTypeProvider_h

#include "SimpitMessageType.h"

#define SimpitMessageTypeProvider_BufferIncrement 10

class SimpitMessageTypeProvider
{
private:
    byte _incomingCount;
    IncomingSimpitMessageType *_incoming;

    byte _outgoingCount;
    OutgoingSimpitMessageType *_outgoing;

public:
    SimpitMessageTypeProvider(uint16_t capacity);
    ~SimpitMessageTypeProvider();

    bool TryGetIncomingMessageType(byte id, IncomingSimpitMessageType *&messageType);

    bool TryGetOutgoingMessageType(byte id, OutgoingSimpitMessageType *&messageType);

    template<typename T> bool RegisterIncoming()
    {
        if(_incomingCount % SimpitMessageTypeProvider_BufferIncrement == 0)
        { // Time to resize the incoming buffer
            IncomingSimpitMessageType* newIncoming = (IncomingSimpitMessageType*)malloc(sizeof(IncomingSimpitMessageType*) * (_incomingCount + SimpitMessageTypeProvider_BufferIncrement));
            for(int i=0; i<_incomingCount; i++)
            {
                newIncoming[i] = _incoming[i];
            }

            free(_incoming);
            _incoming = newIncoming;
        }

        IncomingSimpitMessageType *messageType;
        if(this->TryGetIncomingMessageType(GenericIncomingSimpitMessageType<T>::MessageTypeId, SimpitMessageTypeEnum::Incoming, messageType) == true)
        {
            return false;
        }

        _incoming[_incomingCount++] = &GenericIncomingSimpitMessageType<T>::Instance;

        return true;
    }

    template<typename T> bool RegisterOutgoing()
    {
        if(_outgoingCount % SimpitMessageTypeProvider_BufferIncrement == 0)
        { // Time to resize the outgoing buffer
            OutgoingSimpitMessageType* newOutgoing = (OutgoingSimpitMessageType*)malloc(sizeof(OutgoingSimpitMessageType*) * (_outgoingCount + SimpitMessageTypeProvider_BufferIncrement));
            for(int i=0; i<_outgoingCount; i++)
            {
                newOutgoing[i] = _outgoing[i];
            }

            free(_outgoing);
            _outgoing = newOutgoing;
        }

        OutgoingSimpitMessageType *messageType;
        if(this->TryGetOutgoingMessageType(GenericOutgoingSimpitMessageType<T>::MessageTypeId, SimpitMessageTypeEnum::Outgoing, messageType) == true)
        {
            return false;
        }

        _outgoing[_outgoingCount++] = &GenericOutgoingSimpitMessageType<T>::Instance;

        return true;
    }
};

#endif