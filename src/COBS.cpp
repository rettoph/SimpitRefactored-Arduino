#include "COBS.h"

SimpitStream COBS::_buffer = SimpitStream();

bool COBS::TryEncode(SimpitStream &data)
{
    _buffer.Clear();
    data.CopyTo(_buffer);
    data.Clear();

    data.Write(0x69); // A meaningless placeholder. It will get overwritten.
    int lastZero = 0;
    byte distanceLastZero = 1;

    byte placeholder;
    while(_buffer.Length() > 0 && _buffer.TryReadByte(placeholder))
    {
        if(placeholder == 0x0)
        {
            data.Write(distanceLastZero, lastZero);

            data.Write(0x69); // A meaningless placeholder. It will get overwritten.
            lastZero = data.Length() - 1;

            distanceLastZero = 1;
        }
        else
        {
            data.Write(placeholder);
            distanceLastZero++;
        }
    }

    data.Write(distanceLastZero, lastZero);
    data.Write(0x0); // 0x0 indicates end of message

    return true;
}

bool COBS::TryDecode(SimpitStream &data)
{
    _buffer.Clear();
    data.CopyTo(_buffer);
    data.Clear();

    byte nextZero;
    byte placeHolder;

    if(_buffer.TryReadByte(nextZero) == false)
    {
        return false;
    }

    while(_buffer.Length() > 0 && _buffer.TryReadByte(placeHolder))
    {
        if(placeHolder == 0)
        {
            return (_buffer.Length() == 0) && (nextZero == 0x1);
        }

        nextZero--;
        if(nextZero == 0x0)
        {
            data.Write(0x0);
            nextZero = placeHolder;
        }
        else 
        {
            data.Write(placeHolder);
        }
    }

    return false;
}