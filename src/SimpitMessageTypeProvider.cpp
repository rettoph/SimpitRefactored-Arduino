#include "SimpitMessageTypeProvider.h"

SimpitMessageTypeProvider::SimpitMessageTypeProvider(byte incomingCapacity)
{
    _incomingCount = 0;
    _incoming = (IncomingSimpitMessageType*)malloc(sizeof(GenericIncomingSimpitMessageType<int>) * incomingCapacity);
}

SimpitMessageTypeProvider::~SimpitMessageTypeProvider()
{
    free(_incoming);
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