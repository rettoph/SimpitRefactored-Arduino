#ifndef SimpitBuilder_h
#define SimpitBuilder_h

#include <Arduino.h>
#include "SimpitMessageType.h"
#include "Simpit.h"
#include "SimpitMacros.h"
#include "SimpitMessageTypeProvider.h"

class SimpitAddon;

class SimpitBuilder
{
private:
    SimpitMessageTypeProvider* _messageTypes;

public:
    SimpitBuilder();

    template<typename T> SimpitBuilder RegisterIncoming(void(*handler)(void*, T*))
    {
        _messageTypes->TryRegisterIncoming<T>(handler);
        return *this;
    }

    template<typename T> SimpitBuilder RegisterOutgoing()
    {
        return this->RegisterOutgoing<T>([](T a, T b) {
            return memcmp(&a, &b, sizeof(T)) != 0;
        });
    }

    template<typename T> SimpitBuilder RegisterOutgoing(bool(*delta)(T, T))
    {
        _messageTypes->TryRegisterOutgoing<T>(delta);
        return *this;
    }

    SimpitBuilder RegisterAddon(SimpitAddon *addon);

    Simpit* Build(Stream &serial);
};

#endif