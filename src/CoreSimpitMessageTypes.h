#ifndef CoreSimpitMessageTypes_h
#define CoreSimpitMessageTypes_h

#include "FixedString.h"
#include "CoreSimpitMessageTypeIds.h"

#define SIMPIT_CORE_MESSAGE_TYPE_BUFFER_SIZE 32

enum struct SynchronisationMessageTypeEnum : byte
{
    SYN = 0x0,
    SYNACK = 0x1,
    ACK = 0x2
};

struct __attribute__((packed)) Synchronisation
{
    SynchronisationMessageTypeEnum Type;
    FixedString Version;
};

struct __attribute__((packed)) Handshake
{
    byte HandshakeType;
    byte Payload;
};

struct __attribute__((packed)) EchoRequest
{
    static constexpr byte NullChar = '\0';

    byte Data[SIMPIT_CORE_MESSAGE_TYPE_BUFFER_SIZE];

    void Write(String value)
    {
        value += NullChar;
        for(int i = 0; i < min(value.length(), SIMPIT_CORE_MESSAGE_TYPE_BUFFER_SIZE); i++)
        {
            this->Data[i] = value[i];
        }
    }
};

struct __attribute__((packed)) EchoResponse
{
    static constexpr byte NullChar = '\0';

    byte Data[SIMPIT_CORE_MESSAGE_TYPE_BUFFER_SIZE];

    String ReadString()
    {
        String value = "";

        for(int i = 0; i < SIMPIT_CORE_MESSAGE_TYPE_BUFFER_SIZE; i++)
        {
            if(this->Data[i] == NullChar)
            {
                break;
            }

            value += this->Data[i];
        }

        return value;
    }
};

struct __attribute__((packed)) CloseSerialPort
{
};

struct __attribute__((packed)) RegisterHandler
{
    byte MessageTypeIds[SIMPIT_CORE_MESSAGE_TYPE_BUFFER_SIZE];

    template<typename T> RegisterHandler Add()
    {
        for(int i=0; i < SIMPIT_CORE_MESSAGE_TYPE_BUFFER_SIZE; i++)
        {
            if(this->MessageTypeIds[i] == 0x0)
            {
                this->MessageTypeIds[i] = GenericIncomingSimpitMessageType<T>::MessageTypeId;
                return *this;
            }
        }

        return *this;
    }

    template<typename T> RegisterHandler Add(byte index)
    {
        this->MessageTypeIds[index] = GenericIncomingSimpitMessageType<T>::MessageTypeId;
        return *this;
    }
};

struct __attribute__((packed)) DeregisterHandler
{
    byte MessageTypeIds[SIMPIT_CORE_MESSAGE_TYPE_BUFFER_SIZE];

    template<typename T> DeregisterHandler Add()
    {
        for(int i=0; i < SIMPIT_CORE_MESSAGE_TYPE_BUFFER_SIZE; i++)
        {
            if(this->MessageTypeIds[i] == 0x0)
            {
                this->MessageTypeIds[i] = GenericIncomingSimpitMessageType<T>::MessageTypeId;
                return *this;
            }
        }

        return *this;
    }

    template<typename T> DeregisterHandler Add(byte index)
    {
        this->MessageTypeIds[index] = GenericIncomingSimpitMessageType<T>::MessageTypeId;
        return *this;
    }
};

enum struct CustomLogFlags : byte
{
    None = 0,
    Verbose = 1,
    PrintToScreen = 2,
    NoHeader = 4
};

struct __attribute__((packed)) CustomLog
{
    CustomLogFlags Flags;
    FixedString Value;
};

struct __attribute__((packed)) Request
{
    byte MessageTypeId;
};

#endif