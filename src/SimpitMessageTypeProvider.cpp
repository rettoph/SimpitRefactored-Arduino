#include "SimpitMessageTypeProvider.h"

SimpitMessageTypeProvider::SimpitMessageTypeProvider(byte incomingCapacity, byte outgoingCapacity)
{
    _incomingCount = 0;
    _incoming = (IncomingSimpitMessageType**)malloc(sizeof(IncomingSimpitMessageType**) * incomingCapacity);

    _outgoingCount = 0;
    _outgoing = (OutgoingSimpitMessageType**)malloc(sizeof(OutgoingSimpitMessageType**) * outgoingCapacity);
}

SimpitMessageTypeProvider::~SimpitMessageTypeProvider()
{
    free(_incoming);
    free(_outgoing);
}

int SimpitMessageTypeProvider::PublishIncoming(void* sender, SimpitStream simpit)
{
    int count = 0;

    for(int i = 0; i < _incomingCount; i++)
    {
        if(_incoming[i]->TryPublish(sender, simpit) == true)
        {
            count++;
        }
    }

    return count;
}

bool SimpitMessageTypeProvider::TryGetOutgoingMessageType(byte id, OutgoingSimpitMessageType *&messageType)
{
    for(int i = 0; i < _outgoingCount; i++)
    {
        messageType = *&_outgoing[i];

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
        messageType = *&_incoming[i];

        if(messageType->Id != id)
        {
            continue;
        }

        return true;
    }

    return false;
}