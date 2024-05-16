#include "FixedString.h"

FixedString::FixedString()
{
    memset(_buffer, FixedString::NullChar, FixedString::BufferSize);
}

FixedString::FixedString(char *value, int length)
{
    this->Set(value, length);
}

FixedString::FixedString(String value)
{
    this->Set(value);
}

String FixedString::Get()
{
    int length = FixedString::BufferSize;
    for(unsigned int i=0; i<FixedString::BufferSize; i++)
    {
        if(_buffer[i] == FixedString::NullChar)
        {
            length = i;
            break;
        }
    }

    String value = F("");
    for(unsigned int i = 0; i < length; i++)
    {
        value += _buffer[i];
    }

    return value;
}

void FixedString::Set(char *value, int length)
{
    for(unsigned int i=0; i<FixedString::BufferSize; i++)
    {
        if(i < length)
        {
            _buffer[i] = value[i];
        }
        else
        {
            _buffer[i] = FixedString::NullChar;
        }
    }
}

void FixedString::Set(String value)
{
    this->Set(value.begin(), value.length());
}