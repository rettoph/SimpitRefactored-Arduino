#ifndef CheckSum_h
#define CheckSum_h

#include "SimpitStream.h"

class CheckSum
{
public:
    static byte CalculateCheckSum(SimpitStream &stream);
    static bool ValidateCheckSum(SimpitStream &stream);
};

#endif