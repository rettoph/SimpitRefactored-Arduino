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

    virtual bool TryPublish(void* sender) = 0;

    virtual void SetLatest(SimpitStream incoming) = 0;

    virtual void* GetLatest() = 0;
};

template<typename T> struct GenericIncomingSimpitMessageType : public IncomingSimpitMessageType
{
private:
    bool _dirty;
    T _latest;
    void(*_handler)(void*, T*);

public:
    static const byte MessageTypeId;

    GenericIncomingSimpitMessageType(byte id, void(*handler)(void*, T*)) : IncomingSimpitMessageType(id)
    {
        _handler = handler;
        _dirty = false;

        this->Id = id;
    }

    bool TryPublish(void* sender) override
    {
        if(_dirty == false)
        {
            return false;
        }

        _handler(sender, &_latest);
        _dirty = false;
        return true;
    }

    void SetLatest(SimpitStream incoming) override
    {
        incoming.TryReadBytes(sizeof(T), &_latest);
        _dirty = true;
    }

    void* GetLatest() override
    {
        return &_latest;
    }
};

struct OutgoingSimpitMessageType
{
    byte Id;

    OutgoingSimpitMessageType(byte id)
    {
        this->Id = id;
    }

    virtual void Publish(SerialPort* serial, void* data) = 0;
};

template<typename T> struct GenericOutgoingSimpitMessageType : public OutgoingSimpitMessageType
{
public:
    static const byte MessageTypeId;

    GenericOutgoingSimpitMessageType(byte id) : OutgoingSimpitMessageType(id)
    {
    }

    void Publish(SerialPort* serial, void* data) override
    {
        serial->TryWriteOutgoing(this->Id, (void*)data, sizeof(T));
    }
};

// template<typename T> struct GenericOutgoingSimpitMessageType : public OutgoingSimpitMessageType
// {
// private:
//     T _latest;
//     bool(*_delta)(T, T);
// 
// public:
//     static const byte MessageTypeId;
// 
//     GenericOutgoingSimpitMessageType(byte id, bool(*delta)(T, T)) : OutgoingSimpitMessageType(id)
//     {
//         _latest = T();
//         _delta = delta;
//     }
// 
//     void Publish(SerialPort* serial, void* data) override
//     {
//         T* casted = (T*)data;
//         if(_delta(_latest, *casted) == false)
//         { // No change detected
//             return;
//         }
// 
//         serial->TryWriteOutgoing(this->Id, (void*)data, sizeof(T));
// 
//         memccpy(casted, &_latest, 0, sizeof(T));
//     }
// 
//     void* GetLatest() override
//     {
//         return &_latest;
//     }
// };

#endif