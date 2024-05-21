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
    byte MessageTypeIds[SIMPIT_CORE_MESSAGE_TYPE_BUFFER_SIZE];
};

struct __attribute__((packed)) EchoResponse
{
    byte MessageTypeIds[SIMPIT_CORE_MESSAGE_TYPE_BUFFER_SIZE];
};

struct __attribute__((packed)) CloseSerialPort
{
};

struct __attribute__((packed)) RegisterHandler
{
    byte MessageTypeIds[SIMPIT_CORE_MESSAGE_TYPE_BUFFER_SIZE];
};

struct __attribute__((packed)) DeregisterHandler
{
    byte MessageTypeIds[SIMPIT_CORE_MESSAGE_TYPE_BUFFER_SIZE];
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