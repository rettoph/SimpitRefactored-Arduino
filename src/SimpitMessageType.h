#ifndef SimpitMessageType_h
#define SimpitMessageType_h

#include <Arduino.h>
#include "SimpitMessageSubscriber.h"
#include "SimpitStream.h"

enum SimpitMessageTypeEnum { 
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
    virtual void Publish(SimpitStream incoming) = 0;
};

template<typename T> class IncomingSimpitMessageType : public BaseIncomingSimpitMessageType
{
private: 
    bool _subscribed;
    SimpitMessageSubscriber<T> *_subscriber;
    T* _latest;
 
public:
    IncomingSimpitMessageType(byte id, SimpitMessageTypeEnum type) : BaseSimpitMessageType(id, type)
    {
        _subscribed = false;
        _latest = (T*)malloc(sizeof(T));
    }

    void Publish(SimpitStream incoming) override
    {
        if(_subscribed == false)
        {
            incoming.Clear();
            return;
        }

        if(incoming.TryReadBytes(sizeof(T), _latest) == false)
        {
            incoming.Clear();
            return;
        }

        _subscriber->Process(_latest);
    }

    void Subscribe(SimpitMessageSubscriber<T> *subscriber)
    {
        _subscriber = subscriber;
        _subscribed = true;
    }

    void Unsubscribe()
    {
        _subscribed = false;
    }
};

class BaseOutgoingSimpitMessageType : public BaseSimpitMessageType
{
public:
    virtual void Publish(SimpitStream incoming) = 0;
};

template<typename T> class IncomingSimpitMessageType : public BaseIncomingSimpitMessageType
{
private: 
    bool _subscribed;
    SimpitMessageSubscriber<T> *_subscriber;
    T* _latest;
 
public:
    IncomingSimpitMessageType(byte id, SimpitMessageTypeEnum type) : BaseSimpitMessageType(id, type)
    {
        _subscribed = false;
        _latest = (T*)malloc(sizeof(T));
    }

    void Publish(SimpitStream incoming) override
    {
        if(_subscribed == false)
        {
            incoming.Clear();
            return;
        }

        if(incoming.TryReadBytes(sizeof(T), _latest) == false)
        {
            incoming.Clear();
            return;
        }

        _subscriber->Process(_latest);
    }

    void Subscribe(SimpitMessageSubscriber<T> *subscriber)
    {
        _subscriber = subscriber;
        _subscribed = true;
    }

    void Unsubscribe()
    {
        _subscribed = false;
    }
};

#endif