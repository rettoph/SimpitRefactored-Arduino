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

    virtual void Publish(void* sender, SimpitStream incoming) = 0;
};

template<typename T> struct GenericIncomingSimpitMessageType : public IncomingSimpitMessageType
{
private:
    T _latest;
    void(*_handler)(void*, T*);

public:
    static const byte MessageTypeId;

    GenericIncomingSimpitMessageType(byte id, void(*handler)(void*, T*)) : IncomingSimpitMessageType(id)
    {
        _handler = handler;

        this->Id = id;
    }

    void Publish(void* sender, SimpitStream incoming) override
    {
        incoming.TryReadBytes(sizeof(T), &_latest);
        _handler(sender, &_latest);
    }
};

struct OutgoingSimpitMessageType
{
    byte Id;

    OutgoingSimpitMessageType(byte id)
    {
        this->Id = id;
    }

    virtual void Publish(SerialPort* serial, void* data) const = 0;
};

template<typename T> struct GenericOutgoingSimpitMessageType : public OutgoingSimpitMessageType
{
    static const byte MessageTypeId;

    GenericOutgoingSimpitMessageType(byte id) : OutgoingSimpitMessageType(id)
    {
        
    }

    void Publish(SerialPort* serial, void* data) const override
    {
        serial->TryWriteOutgoing(this->Id, (void*)data, sizeof(T));
    }
};

#endif