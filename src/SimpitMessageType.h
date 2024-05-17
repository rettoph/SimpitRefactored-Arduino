#ifndef SimpitMessageType_h
#define SimpitMessageType_h

#include <Arduino.h>

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

    virtual void Publish(void *data) = 0;
};

template<typename T> class SimpitMessageType : public BaseSimpitMessageType
{
public:
    SimpitMessageType(byte id, SimpitMessageTypeEnum type) : BaseSimpitMessageType(id, type)
    {

    }

    void Publish(void *data) override
    {

    }
};

#endif