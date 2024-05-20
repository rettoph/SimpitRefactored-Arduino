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

struct Synchronisation
{
    SynchronisationMessageTypeEnum Type;
    FixedString Version;
} __attribute__((packed));

struct Handshake
{
    byte HandshakeType;
    byte Payload;
} __attribute__((packed));

struct EchoRequest
{
    byte MessageTypeIds[SIMPIT_CORE_MESSAGE_TYPE_BUFFER_SIZE];
} __attribute__((packed));

struct EchoResponse
{
    byte MessageTypeIds[SIMPIT_CORE_MESSAGE_TYPE_BUFFER_SIZE];
} __attribute__((packed));

struct CloseSerialPort
{
} __attribute__((packed));

struct RegisterHandler
{
    byte MessageTypeIds[SIMPIT_CORE_MESSAGE_TYPE_BUFFER_SIZE];
} __attribute__((packed));

struct DeregisterHandler
{
    byte MessageTypeIds[SIMPIT_CORE_MESSAGE_TYPE_BUFFER_SIZE];
} __attribute__((packed));

enum struct CustomLogFlags : byte
{
    None = 0,
    Verbose = 1,
    PrintToScreen = 2,
    NoHeader = 4
};

struct CustomLog
{
    CustomLogFlags Flags;
    FixedString Value;
} __attribute__((packed));

struct Request
{
    byte MessageTypeId;
} __attribute__((packed));

#endif