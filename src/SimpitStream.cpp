#include "SimpitStream.h"

SimpitStream::SimpitStream()
{
    _readIndex = 0;
    _writeIndex = 0;
    _mode = None;
}

bool SimpitStream::SetMode(SimpitStreamModeEnum mode, int& index)
{
    if(_mode == mode)
    {
        return false;
    }

    index = 0;
    _mode = mode;

    return true;
}

SimpitStreamModeEnum SimpitStream::GetMode()
{
    return _mode;
}

unsigned int SimpitStream::Length()
{
    return _writeIndex - _readIndex;
}

void SimpitStream::Write(byte value)
{
    if(this->SetMode(SimpitStreamModeEnum::Write, _writeIndex))
    {
        _readIndex = 0;
    }

    _buffer[_writeIndex++] = value;
}

void SimpitStream::Write(void* values, int size)
{
    if(this->SetMode(SimpitStreamModeEnum::Write, _writeIndex))
    {
        _readIndex = 0;
    }

    byte* ptr = (byte*)values;

    for(int i=0; i<size; i++)
    {
        _buffer[_writeIndex++] = ptr[i];
    }
}

void SimpitStream::Write(byte value, int index)
{
    if(this->SetMode(SimpitStreamModeEnum::Write, _writeIndex))
    {
        _readIndex = 0;
    }

    _buffer[index] = value;
    _writeIndex = max(_writeIndex, index);
}

void SimpitStream::Write(String value)
{
    int length = value.length();
    this->Write(&length, sizeof(int));

    bool hasDataLeft = true;
    for(unsigned int i = 0; i < length; i++)
    {
        _buffer[_writeIndex++] = value[i];
    }
}

byte SimpitStream::Pop()
{
    if(_writeIndex <= 0)
    {
        return 0;
    }

    return _buffer[--_writeIndex];
}

byte SimpitStream::Peek(int index)
{
    return _buffer[index];
}

bool SimpitStream::TryReadByte(byte &output)
{
    return this->TryReadBytes(sizeof(byte), &output);
}

bool SimpitStream::TryReadBytes(int length, void *output)
{
    this->SetMode(SimpitStreamModeEnum::Read, _readIndex);

    if(this->Length() < length)
    {
        return false;
    }

    byte* ptr = (byte*)output;
    for(int i=0; i<length; i++)
    {
        ptr[i] = _buffer[_readIndex++];
    }

    return true;
}

bool SimpitStream::TryReadString(String *output)
{
    int length;
    if(this->TryReadBytes(sizeof(int), &length) == false)
    {
        return false;
    }

    if(output->reserve(length) == false)
    {
        return false;
    }

    if(this->TryReadBytes(length, output->begin()) == false)
    {
        return false;
    }

    return true;
}

void SimpitStream::Clear()
{
    _writeIndex = 0;
    _readIndex = 0;
    _mode = SimpitStreamModeEnum::None;
}

void SimpitStream::CopyTo(SimpitStream &target)
{
    target._readIndex = _readIndex;
    target._writeIndex = _writeIndex;
    target._mode = _mode;

    for(int i = 0; i < _writeIndex; i++)
    {
        target._buffer[i] = _buffer[i];
    }
}