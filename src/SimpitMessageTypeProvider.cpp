#include "SimpitMessageTypeProvider.h"

SimpitMessageTypeProvider::SimpitMessageTypeProvider(uint16_t capacity)
{
    _incomingCount = 0;
    _incoming = (IncomingSimpitMessageType*)malloc(sizeof(IncomingSimpitMessageType*) * SimpitMessageTypeProvider_BufferIncrement);

    _outgoingCount = 0;
    _outgoing = (OutgoingSimpitMessageType*)malloc(sizeof(OutgoingSimpitMessageType*) * SimpitMessageTypeProvider_BufferIncrement);
}

bool SimpitMessageTypeProvider::TryGetOutgoingMessageType(byte id, OutgoingSimpitMessageType *&messageType)
{
    for(int i = 0; i < _outgoingCount; i++)
    {
        messageType = &_outgoing[i];

        if(messageType->Id != id)
        {
            continue;
        }

        return true;
    }

    return false;
}

bool SimpitMessageTypeProvider::TryGetIncomingMessageType(byte id, IncomingSimpitMessageType *&messageType)
{
    for(int i = 0; i < _incomingCount; i++)
    {
        messageType = &_incoming[i];

        if(messageType->Id != id)
        {
            continue;
        }

        return true;
    }

    return false;
}