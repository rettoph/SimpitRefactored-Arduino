#ifndef SimpitMessageType_h
#define SimpitMessageType_h

#include <Arduino.h>
#include "SimpitStream.h"
#include "SerialPort.h"
#include "function_objects.h"

enum struct SimpitMessageTypeEnum { 
    Unknown, 
    Incoming, 
    Outgoing 
};

struct BaseSimpitMessageType
{
public:
    byte Id;
    SimpitMessageTypeEnum Type;

    BaseSimpitMessageType(byte id, SimpitMessageTypeEnum type);
};

struct BaseIncomingSimpitMessageType : public BaseSimpitMessageType
{
public:
    BaseIncomingSimpitMessageType(byte id, SimpitMessageTypeEnum type) : BaseSimpitMessageType(id, type)
    {

    }

    virtual void Publish(void* sender, SimpitStream incoming) = 0;
};

template<typename T> struct IncomingSimpitMessageType : public BaseIncomingSimpitMessageType
{
private: 
    bool _hasHandler;
    FunctionObject<void(void*, T*)> _handler;
    T _latest;
 
public:
    static const IncomingSimpitMessageType<T> PROGMEM Instance;

    static const byte MessageTypeId;

    IncomingSimpitMessageType() : BaseIncomingSimpitMessageType(IncomingSimpitMessageType<T>::MessageTypeId, SimpitMessageTypeEnum::Incoming)
    {
        _hasHandler = false;
        _latest = T();
    }

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

    void RegisterHandler(FunctionObject<void(void*, T*)> handler)
    {
        _handler = handler;
        _hasHandler = true;
    }
};

struct BaseOutgoingSimpitMessageType : public BaseSimpitMessageType
{
public:
    BaseOutgoingSimpitMessageType(byte id, SimpitMessageTypeEnum type) : BaseSimpitMessageType(id, type)
    {
        
    }
};

template<typename T> struct OutgoingSimpitMessageType : public BaseOutgoingSimpitMessageType
{
private: 
    T _latest;
 
public:
    static const OutgoingSimpitMessageType<T> PROGMEM Instance;

    static const byte MessageTypeId;

    OutgoingSimpitMessageType() : BaseOutgoingSimpitMessageType(OutgoingSimpitMessageType<T>::MessageTypeId, SimpitMessageTypeEnum::Outgoing)
    {
        _latest = T();
    }

    void Publish(SerialPort* serial, T* data)
    {
        serial->TryWriteOutgoing(this->Id, (void*)data, sizeof(T));
    }
};

#endif