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
        const BaseSimpitMessageType* messageType;
        if(_messageTypes->TryGetMessageType(OutgoingSimpitMessageType<T>::MessageTypeId, SimpitMessageTypeEnum::Outgoing, *&messageType) == false)
        {
            return; // TODO: Some sort of error handling here
        }

        OutgoingSimpitMessageType<T>* casted = (OutgoingSimpitMessageType<T>*)messageType;
        casted->Publish(_serial, &data);
    }

    void Log(String value);
    void Log(String value, CustomLogFlags flags);
};

#endif