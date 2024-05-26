#ifndef UnmanagedString_h
#define UnmanagedString_h

#include <Arduino.h>

#define SIMPIT_FIXED_STRING_BUFFER_SIZE 32

struct FixedString
{
private:
    static constexpr char NullChar = '\0';

    char _buffer[SIMPIT_FIXED_STRING_BUFFER_SIZE];

public:
    FixedString();
    FixedString(char *value, int length);
    FixedString(String value);

    String Get();

    void Set(char *value, int length);
    void Set(String value);
} __attribute__((packed));

#endif