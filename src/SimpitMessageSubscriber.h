#ifndef SimpitMessageSubscriber_h
#define SimpitMessageSubscriber_h

#include <Arduino.h>
#include "SimpitStream.h"

class BaseSimpitMessageSubscriber
{
};

template <typename T> class SimpitMessageSubscriber : public BaseSimpitMessageSubscriber
{
    virtual void Process(T);
};

#endif