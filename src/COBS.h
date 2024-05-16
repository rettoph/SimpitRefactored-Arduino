#ifndef COBS_h
#define COBS_h

#include <Arduino.h>
#include "SimpitStream.h"

class COBS
{
private:
    static SimpitStream _buffer;

public:
    static bool TryEncode(SimpitStream &data);

    static bool TryDecode(SimpitStream &data);
};

#endif