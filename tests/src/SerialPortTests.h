#include <Arduino.h>
#include <AUnit.h>
#include <MemStream.h>
#include <SerialPort.h>

using namespace aunit;

class SerialPortTests: public TestOnce
{
public:
    byte buffer[256];

    MemStream *stream;
    SerialPort *serial;

    SerialPortTests()
    {
        stream = new MemStream(buffer, 256, 0, true);
        serial = new SerialPort(*stream);
    }

    void Reset()
    {
        memset(buffer, 0x0, 256);
        stream->setBufferContentPosition(0, 0);
    }
};

testF(SerialPortTests, write_read_matches_write)
{
    const byte messageTypeId = 0x69;

    const unsigned int dataSize = 16;
    const byte *data = new byte[16] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

    SimpitStream *incoming = new SimpitStream();

    assertTrue(serial->TryWriteOutgoing(0x69, (void*)data, dataSize));
    assertTrue(serial->TryReadIncoming(incoming));

    assertEqual(incoming->Length(), (unsigned int)sizeof(messageTypeId) + dataSize);

    byte placeholder;
    assertTrue(incoming->TryReadByte(placeholder));
    assertEqual(placeholder, messageTypeId);

    for(int i = 0; i < dataSize; i++)
    {
        assertTrue(incoming->TryReadByte(placeholder));
        assertEqual(data[i], placeholder);
    }

    assertEqual(incoming->Length(), (unsigned int)0);
}