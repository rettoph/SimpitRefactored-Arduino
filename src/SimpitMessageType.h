#ifndef SimpitMessageType_h
#define SimpitMessageType_h

#include <Arduino.h>
#include "SimpitStream.h"
#include "SerialPort.h"

enum struct SimpitMessageTypeEnum { 
    Unknown, 
    Incoming, 
    Outgoing 
};

class BaseSimpitMessageType
{
public:
    byte Id;
    SimpitMessageTypeEnum Type;

    BaseSimpitMessageType(byte id, SimpitMessageTypeEnum type);
};

class BaseIncomingSimpitMessageType : public BaseSimpitMessageType
{
public:
    BaseIncomingSimpitMessageType(byte id, SimpitMessageTypeEnum type) : BaseSimpitMessageType(id, type)
    {

    }

    virtual void Publish(void* sender, SimpitStream incoming) = 0;
};

template<typename T> class IncomingSimpitMessageType : public BaseIncomingSimpitMessageType
{
private: 
    bool _hasCallback;
    void (*_callback)(void*, T*);
    T* _latest;
 
public:
    static const byte MessageTypeId;

    IncomingSimpitMessageType(byte id, SimpitMessageTypeEnum type) : BaseIncomingSimpitMessageType(id, type)
    {
        _hasCallback = false;
        _latest = (T*)malloc(sizeof(T));
    }

    void Publish(void* sender, SimpitStream incoming) override
    {
        if(_hasCallback == false)
        {
            incoming.Clear();
            return;
        }

        if(incoming.TryReadBytes(sizeof(T), _latest) == false)
        {
            incoming.Clear();
            return;
        }

        _callback(sender, _latest);
    }

    void RegisterCallback(void (*callback)(void*, T*))
    {
        _callback = callback;
        _hasCallback = true;
    }
};

class BaseOutgoingSimpitMessageType : public BaseSimpitMessageType
{
public:
    BaseOutgoingSimpitMessageType(byte id, SimpitMessageTypeEnum type) : BaseSimpitMessageType(id, type)
    {
        
    }
};

template<typename T> class OutgoingSimpitMessageType : public BaseOutgoingSimpitMessageType
{
private: 
    T* _latest;
 
public:
    static const byte MessageTypeId;

    OutgoingSimpitMessageType(byte id, SimpitMessageTypeEnum type) : BaseOutgoingSimpitMessageType(id, type)
    {
        _latest = (T*)malloc(sizeof(T));
    }

    void Publish(SerialPort* serial, T* data)
    {
        serial->TryWriteOutgoing(this->Id, (void*)data, sizeof(T));
    }
};

#endif