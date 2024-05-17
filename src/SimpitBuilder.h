#ifndef SimpitBuilder_h
#define SimpitBuilder_h

#include <Arduino.h>
#include "SimpitMessageType.h"

class SimpitBuilder
{
private:
    uint16_t _typeCount;
    BaseSimpitMessageType **_types;

public:
    SimpitBuilder();

    template<typename T> void RegisterIncoming(byte messageTypeId)
    {
        _types[_typeCount++] = new SimpitMessageType<T>(messageTypeId, SimpitMessageTypeEnum::Incoming);
    }

    BaseSimpitMessageType** Build();
};

#endif