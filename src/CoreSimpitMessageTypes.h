#ifndef CoreSimpitMessageTypes_h
#define CoreSimpitMessageTypes_h

#include "FixedString.h"
#include "SimpitMessageData.h"

enum struct SynchronisationMessageTypeEnum : byte
{
    SYN = 0x0,
    SYNACK = 0x1,
    ACK = 0x2
};

struct Synchronisation : public SimpitMessageData
{
    static const byte MessageTypeId = 0; // Outgoing

    SynchronisationMessageTypeEnum Type;
    FixedString Version;
} __attribute__((packed));

struct Handshake : public SimpitMessageData
{
    static const byte MessageTypeId = 0; // Incoming

    byte HandshakeType;
    byte Payload;
} __attribute__((packed));

enum struct CustomLogFlags : byte
{
    None = 0,
    Verbose = 1,
    PrintToScreen = 2,
    NoHeader = 4
};

struct CustomLog : public SimpitMessageData
{
    static const byte MessageTypeId = 25; // Outgoing

    CustomLogFlags Flags;
    FixedString Value;
} __attribute__((packed));

#endif