#include "SerialPort.h"

#include <Arduino.h>
#include "COBS.h"
#include "CheckSum.h"

SerialPort::SerialPort(Stream &serial)
{
    _serial = &serial;
    _incoming = new SimpitStream();
    _outgoing = new SimpitStream();
}

bool SerialPort::TryReadIncoming(SimpitStream &incoming)
{
    _incoming->Clear();

    while(_serial->available())
    {
        byte data = _serial->read();
        _incoming->Write(data);
        if(data != 0x0) // 0x0 indicates end of message
        {
            continue;
        }

        if(COBS::TryDecode(*_incoming) == false)
        {
            return false;
        }

        if(CheckSum::ValidateCheckSum(*_incoming) == false)
        {
            return false;
        }

        incoming.Clear();
        _incoming->CopyTo(incoming);

        return true;
    }

    return false;
}

bool SerialPort::TryWriteOutgoing(byte messageTypeId, void* data, unsigned int size)
{
    // Write raw data
    _outgoing->Clear();
    _outgoing->Write(messageTypeId);
    _outgoing->Write(data, size);

    // Calculate and append checksum
    byte checksum = CheckSum::CalculateCheckSum(*_outgoing);
    _outgoing->Write(checksum);

    // COBS encode data
    if(COBS::TryEncode(*_outgoing) == false)
    {
        return false;
    }

    // Write data to serial stream
    byte outgoing;
    while(_outgoing->TryReadByte(outgoing))
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