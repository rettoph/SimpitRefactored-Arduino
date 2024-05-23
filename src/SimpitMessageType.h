#ifndef SimpitMessageType_h
#define SimpitMessageType_h

#include <Arduino.h>
#include "SimpitStream.h"
#include "SerialPort.h"

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
    void(*_handler)(void*, T*);

public:
    static const byte MessageTypeId;

    GenericIncomingSimpitMessageType(byte id, void(*handler)(void*, T*)) : IncomingSimpitMessageType(id)
    {
        _handler = handler;

        this->Id = id;
    }

    bool TryPublish(void* sender, SimpitStream incoming) override
    {
        T value;
        if(incoming.TryReadBytes(sizeof(T), &value) == false)
        {
            return false;
        }

        _handler(sender, &value);
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