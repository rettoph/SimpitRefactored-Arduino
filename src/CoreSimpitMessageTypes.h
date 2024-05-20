#ifndef CoreSimpitMessageTypes_h
#define CoreSimpitMessageTypes_h

#include "FixedString.h"
#include "SimpitMessageData.h"

enum SynchronisationMessageTypeEnum : byte
{
    SYN = 0x0,
    SYNACK = 0x1,
    ACK = 0x2
};

struct Synchronisation : public SimpitMessageData
{
    static const byte MessageTypeId = 0;

    SynchronisationMessageTypeEnum Type;
    FixedString Version;
} __attribute__((packed));

#endif