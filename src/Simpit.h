#ifndef Simpit_h
#define Simpit_h

#include "SimpitMessageType.h"
#include "SerialPort.h"

class Simpit
{
private:
    uint16_t _typeCount;
    BaseSimpitMessageType **_types;
    SerialPort* _serial;
    SimpitStream _buffer;

    bool TryGetMessageType(byte id, BaseSimpitMessageType *&messageType);

public:
    Simpit(BaseSimpitMessageType **types, uint16_t typeCount, Stream &serial);

    int ReadIncoming();

    template<typename T> void Subscribe(SimpitMessageSubscriber<T>* subscriber)
    {
        BaseSimpitMessageType* messageType;
        if(this->TryGetMessageType(T::MessageTypeId, *&messageType) == false)
        {
            return; // TODO: Some sort of error handling here
        }

        IncomingSimpitMessageType<T>* casted = (IncomingSimpitMessageType<T>*)messageType;
        casted->Subscribe(subscriber);
    }
};

#endif