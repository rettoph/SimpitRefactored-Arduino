#include "SerialPort.h"

#include <Arduino.h>
#include "COBS.h"
#include "CheckSum.h"

void EnsureEmptySerial(Stream *serial)
{
    while(serial->available())
    {
        serial->read();
    }
}

SerialPort::SerialPort(Stream &serial)
{
    _serial = &serial;
    _buffer = SimpitStream();
}

bool SerialPort::TryReadIncoming(SimpitStream *&incoming)
{
    _buffer.Clear();

    while(_serial->available())
    {
        byte data = _serial->read();
        _buffer.Write(data);
        if(data != 0x0) // 0x0 indicates end of message
        {
            continue;
        }

        if(COBS::TryDecode(_buffer) == false)
        {
            return false;
        }

        if(CheckSum::ValidateCheckSum(_buffer) == false)
        {
            return false;
        }

        incoming = &_buffer;

        return true;
    }

    return false;
}

bool SerialPort::TryWriteOutgoing(byte messageTypeId, void* data, unsigned int size)
{
    // Write raw data
    _buffer.Clear();
    _buffer.Write(messageTypeId);
    _buffer.Write(data, size);

    // Calculate and append checksum
    byte checksum = CheckSum::CalculateCheckSum(_buffer);
    _buffer.Write(checksum);

    // COBS encode data
    if(COBS::TryEncode(_buffer) == false)
    {
        return false;
    }

    // Write data to serial stream
    byte outgoing;
    while(_buffer.TryReadByte(outgoing))
    {
        _serial->write(outgoing);
    }

    return true;
}
void SerialPort::Clear()
{
    while(_serial->available())
    {
        _serial->read();
    }
}