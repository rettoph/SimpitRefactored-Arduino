#ifndef SimpitMessageSubscriber_h
#define SimpitMessageSubscriber_h

#include <Arduino.h>

template <typename T> class SimpitMessageSubscriber
{
public:
    virtual void Process(T* data) = 0;
};

#endif