#ifndef UnmanagedString_h
#define UnmanagedString_h

#include <Arduino.h>

struct FixedString
{
public:
    static constexpr unsigned int BufferSize = 32;

private:
    static constexpr byte NullChar = '\0';

    char _buffer[BufferSize];

public:
    FixedString();
    FixedString(char *value, int length);
    FixedString(String value);

    String Get();

    void Set(char *value, int length);
    void Set(String value);
} __attribute__((packed));

#endif