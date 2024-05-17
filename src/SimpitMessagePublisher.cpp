#include "SimpitMessagePublisher.h"


SimpitMessagePublisher::SimpitMessagePublisher()
{
    delete _subscribers;
}

template <typename T> void SimpitMessagePublisher::Publish(T message)
{
    
}