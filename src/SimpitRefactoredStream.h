#ifndef SimpitStream_h
#define SimpitStream_h

#include <Arduino.h>

enum struct SimpitStreamModeEnum : byte { 
    None, 
    Read, 
    Write 
};

class SimpitStream
{

public:
    static constexpr unsigned int BufferSize = 64;

private:
    byte _buffer[BufferSize];
    byte _readIndex;
    byte _writeIndex;
    SimpitStreamModeEnum _mode;

    bool SetMode(SimpitStreamModeEnum mode, byte &index);

public:
    SimpitStream();
    
    unsigned int Length();
    SimpitStreamModeEnum GetMode();

    void Write(byte value);
    void Write(void* values, int size);
    void Write(byte value, byte index);
    void Write(String value);

    byte Pop();
    byte Peek(byte index);
    bool TryPeekBytes(int size, void *output);

    bool TryReadByte(byte &output);
    bool TryReadBytes(int size, void *output);
    bool TryReadString(String *string);

    void Clear();

    void CopyTo(SimpitStream &target);
};

#endif