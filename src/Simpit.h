#ifndef Simpit_h
#define Simpit_h

#include "SimpitMessageType.h"
#include "SerialPort.h"
#include "SimpitMessageTypes.h"
#include "SimpitMessageTypeProvider.h"
#include "IncomingMessageSubscriber.h"

class Simpit
{
private:
    SimpitMessageTypeProvider _messageTypes;
    SerialPort _serial;
    SimpitStream _buffer;

public:
  /** Default constructor. Usually called via SimpitBuilder::Build()
      @param messageTypes Pointer to registered message types
      @param serial The serial instance this instance will use to communicate
      with the plugin. Usually "Serial".
  */
    Simpit(byte incomingMessageHandlerCapacity, Stream &serial);

  /** Initialise the serial connection.
      Performs handshaking with the plugin. Note that the KSPit library
      *does not* call the `begin()` method on the serial object. You'll need
      to ensure you've run `Serial.begin(115200)` (or similar) before calling
      this method.
  */
    bool Init(byte &response);

    int ReadIncoming();

    void Update();

    template<typename T> Simpit& RegisterIncomingSubscriber(void(*subscriber)(void*, T*))
    {
        _messageTypes.TryRegisterIncoming<T>(subscriber);
        return *this;
    }

    template<typename T> Simpit& RegisterIncomingSubscriber(IncomingMessageSubscriber<T> *subscriber)
    {
        _messageTypes.TryRegisterIncoming<T>(subscriber);
        return *this;
    }
    
    template<typename T> Simpit& Register()
    {
        T::Register(this);
        return *this;
    }

    template<typename T> void WriteOutgoing(T data)
    {
        GenericOutgoingSimpitMessageType<T>::Publish(&_serial, &data);
    }

    void SubscribeIncoming(RegisterHandler subscriptions);

    void UnsubscribeIncoming(DeregisterHandler unsubscriptions);

    template<typename T> void SubscribeIncoming()
    {
        RegisterHandler subscription = RegisterHandler();
        subscription.Add<T>();
        this->WriteOutgoing(subscription);
    }

    template<typename T> void UnsubscribeIncoming()
    {
        DeregisterHandler unsubscrption = DeregisterHandler();
        unsubscrption.Add<T>();
        this->WriteOutgoing(unsubscrption);
    }

    template<typename T> void RequestIncoming()
    {
        Request request = Request();
        request.MessageTypeId = GenericIncomingSimpitMessageType<T>::MessageTypeId;

        this->WriteOutgoing(request);
    }

    void Log(String value);
    void Log(String value, CustomLogFlags flags);
};

#endif