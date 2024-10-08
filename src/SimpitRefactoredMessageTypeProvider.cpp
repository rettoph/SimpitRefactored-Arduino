#include "SimpitRefactoredMessageTypeProvider.h"

SimpitMessageTypeProvider::SimpitMessageTypeProvider(byte incomingMessageHandlerCapacity)
{
    _incomingCount = 0;
    _incoming = (IncomingSimpitMessageType**)malloc(sizeof(IncomingSimpitMessageType**) * incomingMessageHandlerCapacity);
}

SimpitMessageTypeProvider::~SimpitMessageTypeProvider()
{
    free(_incoming);
}

bool SimpitMessageTypeProvider::TryGetIncomingMessageType(byte id, IncomingSimpitMessageType *&messageType, byte &index)
{
    while(index < _incomingCount)
    {
        messageType = *&_incoming[index++];

        if(messageType->Id != id)
        {
            continue;
        }

        return true;
    }

    return false;
}