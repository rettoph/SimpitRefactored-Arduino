#ifndef SimpitMessageTypeProvider_h
#define SimpitMessageTypeProvider_h

#include "SimpitRefactoredMessageType.h"
#include "IncomingMessageSubscriber.h"

template<typename T> class LambdaIncomingMessageTypeSubscriber : public IncomingMessageSubscriber<T> {
    private:
        void(*_subscriber)(void*, T*);

    public:
        LambdaIncomingMessageTypeSubscriber(void(*subscriber)(void*, T*))
        {
            this->_subscriber = subscriber;
        }

        void Process(void *sender, T *data) override
        {
            this->_subscriber(sender, data);
        };
};

class SimpitMessageTypeProvider
{
private:
    byte _incomingCount;
    IncomingSimpitMessageType **_incoming;

public:
    SimpitMessageTypeProvider(byte incomingCapacity);
    ~SimpitMessageTypeProvider();

    bool TryGetIncomingMessageType(byte id, IncomingSimpitMessageType *&messageType, byte &index);

    template<typename T> bool TryRegisterIncoming(void(*subscriber)(void*, T*))
    {
        IncomingMessageSubscriber<T> *incomingSubscriber = new LambdaIncomingMessageTypeSubscriber<T>(subscriber);
        return this->TryRegisterIncoming(incomingSubscriber);
    }

    template<typename T> bool TryRegisterIncoming(IncomingMessageSubscriber<T> *subscriber)
    {
        GenericIncomingSimpitMessageType<T>* type = new GenericIncomingSimpitMessageType<T>(GenericIncomingSimpitMessageType<T>::MessageTypeId, subscriber);
        _incoming[_incomingCount++] = (IncomingSimpitMessageType*)type;

        return true;
    }
};

#endif