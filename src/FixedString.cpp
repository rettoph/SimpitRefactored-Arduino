#include "FixedString.h"

FixedString::FixedString()
{
    memset(_buffer, FixedString::NullChar, SIMPIT_FIXED_STRING_BUFFER_SIZE);
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
    String value = F("");
    for(unsigned int i=0; i<SIMPIT_FIXED_STRING_BUFFER_SIZE; i++)
    {
        if(_buffer[i] == FixedString::NullChar)
        {
            break;
        }

        value += _buffer[i];
    }

    return value;
}

void FixedString::Set(char *value, int length)
{
    for(unsigned int i=0; i<SIMPIT_FIXED_STRING_BUFFER_SIZE; i++)
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