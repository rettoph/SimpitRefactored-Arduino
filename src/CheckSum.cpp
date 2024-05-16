#include "CheckSum.h"

byte CheckSum::CalculateCheckSum(SimpitStream &stream)
{
    byte result = stream.Peek(0);
    for(int i = 1; i < stream.Length(); i++)
    {
        result ^= stream.Peek(i);
    }

    return result;
}

bool CheckSum::ValidateCheckSum(SimpitStream &stream)
{
    byte expected = stream.Pop();
    byte calculated = CheckSum::CalculateCheckSum(stream);

    bool valid = calculated == expected;
    return valid;
}