#ifndef SimpitBuilder_h
#define SimpitBuilder_h

#include <Arduino.h>
#include "SimpitMessageType.h"
#include "Simpit.h"
#include "SimpitMacros.h"
#include "SimpitMessageTypeProvider.h"
#include "function_objects.h"

class SimpitAddon;

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

    template<typename T> SimpitBuilder RegisterIncomingHandler(FunctionObject<void(void*, T*)> handler)
    {
        BaseSimpitMessageType* messageType;
        if(_messageTypes->TryGetMessageType(IncomingSimpitMessageType<T>::MessageTypeId, SimpitMessageTypeEnum::Incoming, *&messageType) == false)
        {
            return *this; // TODO: Some sort of error handling here
        }

        IncomingSimpitMessageType<T>* casted = (IncomingSimpitMessageType<T>*)messageType;
        casted->RegisterHandler(handler);

        return *this;
    }

    SimpitBuilder RegisterAddon(SimpitAddon *addon);

    Simpit* Build(Stream &serial);
};

#endif