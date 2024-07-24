#ifndef IncomingMessageSubscriber_h
#define IncomingMessageSubscriber_h

template<typename T> class IncomingMessageSubscriber
{
    public:
        virtual void Process(void *sender, T *data) = 0;
};

#endif