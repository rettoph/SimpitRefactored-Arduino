#ifndef SimpitMessageType_h
#define SimpitMessageType_h

#include <Arduino.h>
#include "SimpitStream.h"
#include "SerialPort.h"
#include "IncomingMessageSubscriber.h"

struct IncomingSimpitMessageType
{
    byte Id;

    IncomingSimpitMessageType(byte id)
    {
        this->Id = id;
    }

    virtual bool TryPublish(void* sender, SimpitStream incoming) = 0;
};

template<typename T> struct GenericIncomingSimpitMessageType : public IncomingSimpitMessageType
{
private:
    IncomingMessageSubscriber<T> *_subscriber;

public:
    static const byte MessageTypeId;

    GenericIncomingSimpitMessageType(byte id, IncomingMessageSubscriber<T> *subscriber) : IncomingSimpitMessageType(id)
    {
        this->_subscriber = subscriber;

        this->Id = id;
    }

    bool TryPublish(void* sender, SimpitStream incoming) override
    {
        T value;
        if(incoming.TryPeekBytes(sizeof(T), &value) == false)
        {
            return false;
        }

        this->_subscriber->Process(sender, &value);

        return true;
    }
};

template<typename T> struct GenericOutgoingSimpitMessageType
{
public:
    static const byte MessageTypeId;

    static void Publish(SerialPort* serial, void* data)
    {
        serial->TryWriteOutgoing(GenericOutgoingSimpitMessageType<T>::MessageTypeId, (void*)data, sizeof(T));
    }
};

#endif