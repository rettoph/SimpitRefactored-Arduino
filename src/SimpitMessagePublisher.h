#ifndef SimpitMessagePublisher_h
#define SimpitMessagePublisher_h

#include <Arduino.h>
#include "SimpitMessageSubscriber.h"

class SimpitMessagePublisher
{
private:
    uint16_t _size;
    void **_subscribers;

public:
    SimpitMessagePublisher();

    template<typename T> void Publish(T message);
    template<typename T> void Subscribe(SimpitMessageSubscriber<T> subscriber);
};

#endif