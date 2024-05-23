#ifndef Simpit_h
#define Simpit_h

#include "SimpitMessageType.h"
#include "SerialPort.h"
#include "CoreSimpitMessageTypes.h"
#include "SimpitMessageTypeProvider.h"

class Simpit
{
private:
    SimpitMessageTypeProvider *_messageTypes;
    SerialPort* _serial;
    RegisterHandler _register;
    DeregisterHandler _deregister;
    SimpitStream _buffer;

public:
  /** Default constructor. Usually called via SimpitBuilder::Build()
      @param messageTypes Pointer to registered message types
      @param serial The serial instance this instance will use to communicate
      with the plugin. Usually "Serial".
  */
    Simpit(SimpitMessageTypeProvider* messageTypes, Stream &serial);

  /** Initialise the serial connection.
      Performs handshaking with the plugin. Note that the KSPit library
      *does not* call the `begin()` method on the serial object. You'll need
      to ensure you've run `Serial.begin(115200)` (or similar) before calling
      this method.
  */
    bool Init(byte response);

    int ReadIncoming();

    void Update();

    template<typename T> void WriteOutgoing(T data)
    {
        GenericOutgoingSimpitMessageType<T>::Publish(_serial, &data);
    }

    template<typename T> bool SubscribeIncoming()
    {
        for(int i=0; i < SIMPIT_CORE_MESSAGE_TYPE_BUFFER_SIZE; i++)
        {
            if(_register.MessageTypeIds[i] == 0x0)
            {
                _register.MessageTypeIds[i] = GenericIncomingSimpitMessageType<T>::MessageTypeId;
                this->RequestIncoming<T>();
                return true;
            }
        }

        return false;
    }

    template<typename T> bool UnsubscribeIncoming()
    {
        for(int i=0; i < SIMPIT_CORE_MESSAGE_TYPE_BUFFER_SIZE; i++)
        {
            if(_deregister.MessageTypeIds[i] == 0x0)
            {
                _deregister.MessageTypeIds[i] = GenericIncomingSimpitMessageType<T>::MessageTypeId;
                return true;
            }
        }

        return false;
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