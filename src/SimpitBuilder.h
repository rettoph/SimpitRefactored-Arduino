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
    SimpitBuilder(byte incomingCapacity, byte outgoingCapacity);

    SimpitBuilder ReserveIncoming(byte count);
    SimpitBuilder ReserveOutgoing(byte count);

    template<typename T> SimpitBuilder RegisterIncoming(void(*handler)(void*, T*))
    {
        _messageTypes->TryRegisterIncoming<T>(handler);
        return *this;
    }

    template<typename T> SimpitBuilder RegisterOutgoing()
    {
        _messageTypes->TryRegisterOutgoing<T>();
        return *this;
    }

    template<typename T> SimpitBuilder Register()
    {
        T::Register(this);
        return *this;
    }

    Simpit* Build(Stream &serial);
};

#endif