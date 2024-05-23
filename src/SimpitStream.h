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
    static constexpr unsigned int BufferSize = 128;

private:
    byte _buffer[BufferSize];
    int _readIndex;
    int _writeIndex;
    SimpitStreamModeEnum _mode;

    bool SetMode(SimpitStreamModeEnum mode, int& index);

public:
    SimpitStream();
    
    unsigned int Length();
    SimpitStreamModeEnum GetMode();

    void Write(byte value);
    void Write(void* values, int size);
    void Write(byte value, int index);
    void Write(String value);

    byte Pop();
    byte Peek(int index);

    bool TryReadByte(byte &output);
    bool TryReadBytes(int size, void *output);
    bool TryReadString(String *string);

    void Clear();

    void CopyTo(SimpitStream &target);
};

#endif