#ifndef Simpit_h
#define Simpit_h

#include "SimpitMessageType.h"
#include "SerialPort.h"
#include "CoreSimpitMessageTypes.h"

class Simpit
{
private:
    uint16_t _typeCount;
    BaseSimpitMessageType **_types;
    SerialPort* _serial;
    SimpitStream _buffer;

    bool TryGetMessageType(byte id, SimpitMessageTypeEnum type, BaseSimpitMessageType *&messageType);

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
    bool Init(byte response);

    int ReadIncoming();

    void Update();

    template<typename T> void WriteOutgoing(T data)
    {
        BaseSimpitMessageType* messageType;
        if(this->TryGetMessageType(OutgoingSimpitMessageType<T>::MessageTypeId, SimpitMessageTypeEnum::Outgoing, *&messageType) == false)
        {
            return; // TODO: Some sort of error handling here
        }

        OutgoingSimpitMessageType<T>* casted = (OutgoingSimpitMessageType<T>*)messageType;
        casted->Publish(_serial, &data);
    }

    template<typename T> void RegisterCallback(void (*callback)(void*, T*))
    {
        BaseSimpitMessageType* messageType;
        if(this->TryGetMessageType(OutgoingSimpitMessageType<T>::MessageTypeId, SimpitMessageTypeEnum::Incoming, *&messageType) == false)
        {
            return; // TODO: Some sort of error handling here
        }

        IncomingSimpitMessageType<T>* casted = (IncomingSimpitMessageType<T>*)messageType;
        casted->RegisterCallback(callback);
    }

    void Log(String value);
    void Log(String value, CustomLogFlags flags);
};

#endif