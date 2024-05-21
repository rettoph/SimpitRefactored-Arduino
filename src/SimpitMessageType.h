#ifndef SimpitMessageType_h
#define SimpitMessageType_h

#include <Arduino.h>
#include "SimpitStream.h"
#include "SerialPort.h"
#include "function_objects.h"

struct SimpitMessageType
{
public:
    byte Id;
};

struct IncomingSimpitMessageType : public SimpitMessageType
{
public:
    virtual void Publish(void* sender, SimpitStream incoming) = 0;
};

template<typename T> struct GenericIncomingSimpitMessageType : public IncomingSimpitMessageType
{
public:
    static GenericIncomingSimpitMessageType<T> PROGMEM Instance;

    void Publish(void* sender, SimpitStream incoming) override
    {
        if(_hasHandler == false)
        {
            incoming.Clear();
            return;
        }

        if(incoming.TryReadBytes(sizeof(T), &_latest) == false)
        {
            incoming.Clear();
            return;
        }

        _handler(sender, &_latest);
    }
};

struct OutgoingSimpitMessageType : public SimpitMessageType
{
};

template<typename T> struct GenericOutgoingSimpitMessageType : public OutgoingSimpitMessageType
{
public:
    static GenericOutgoingSimpitMessageType<T> PROGMEM Instance;

    void Publish(SerialPort* serial, T* data)
    {
        serial->TryWriteOutgoing(this->Id, (void*)data, sizeof(T));
    }
};

#endif