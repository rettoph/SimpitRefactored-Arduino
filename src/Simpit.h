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
  /** Default constructor. Usually called via SimpitBuilder::Build()
      @param types Pointer to registered message types
      @param typeCout Count of total registered message types
      @param serial The serial instance this instance will use to communicate
      with the plugin. Usually "Serial".
  */
    Simpit(BaseSimpitMessageType **types, uint16_t typeCount, Stream &serial);

  /** Initialise the serial connection.
      Performs handshaking with the plugin. Note that the KSPit library
      *does not* call the `begin()` method on the serial object. You'll need
      to ensure you've run `Serial.begin(115200)` (or similar) before calling
      this method.
  */
    bool Init();

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