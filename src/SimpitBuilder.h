#ifndef SimpitBuilder_h
#define SimpitBuilder_h

#include <Arduino.h>
#include "SimpitMessageType.h"
#include "Simpit.h"
#include "SimpitMacros.h"

class SimpitBuilder
{
private:
    uint16_t _typeCount;
    BaseSimpitMessageType **_types;
    bool _deconstructed;

public:
    SimpitBuilder();

    template<typename T> SimpitBuilder RegisterIncoming()
    {
        _types[_typeCount++] = new IncomingSimpitMessageType<T>(IncomingSimpitMessageType<T>::MessageTypeId, SimpitMessageTypeEnum::Incoming);
        return *this;
    }

    template<typename T> SimpitBuilder RegisterOutgoing()
    {
        _types[_typeCount++] = new OutgoingSimpitMessageType<T>(OutgoingSimpitMessageType<T>::MessageTypeId, SimpitMessageTypeEnum::Outgoing);
        return *this;
    }

    Simpit* Build(Stream &serial);
};

#endif