#ifndef SimpitBuilder_h
#define SimpitBuilder_h

#include <Arduino.h>
#include "SimpitMessageType.h"
#include "Simpit.h"
#include "SimpitMacros.h"
#include "SimpitMessageTypeProvider.h"

class SimpitBuilder
{
private:
    SimpitMessageTypeProvider* _messageTypes;

public:
    SimpitBuilder();

    template<typename T> SimpitBuilder RegisterIncoming()
    {
        _messageTypes->TryRegisterIncoming<T>();
        return *this;
    }

    template<typename T> SimpitBuilder RegisterOutgoing()
    {
        _messageTypes->TryRegisterOutgoing<T>();
        return *this;
    }

    template<typename T> void RegisterCallback(void (*callback)(void*, T*))
    {
        BaseSimpitMessageType* messageType;
        if(_messageTypes->TryGetMessageType(OutgoingSimpitMessageType<T>::MessageTypeId, SimpitMessageTypeEnum::Incoming, *&messageType) == false)
        {
            return; // TODO: Some sort of error handling here
        }

        IncomingSimpitMessageType<T>* casted = (IncomingSimpitMessageType<T>*)messageType;
        casted->RegisterCallback(callback);
    }

    Simpit* Build(Stream &serial);
};

#endif