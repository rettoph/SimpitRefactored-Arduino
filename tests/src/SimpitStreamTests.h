#include <Arduino.h>
#include <AUnit.h>
#include <SimpitStream.h>
#include <FixedString.h>

using namespace aunit;

const unsigned int Zero = 0;
const unsigned int One = 1;

class SimpitStreamTests: public TestOnce
{
public:
    SimpitStream *stream;

protected:
    void setup() override {
        TestOnce::setup();

        delete stream;
        stream = new SimpitStream();
    }

    void teardown() override {
        TestOnce::teardown();

        delete stream;
    }
};

testF(SimpitStreamTests, read_write_byte)
{
    byte input = 0x69; // Random test data
    byte output = 0x0;

    stream->Clear();
    assertEqual(stream->Length(), Zero);
    assertTrue(stream->GetMode() == SimpitStreamModeEnum::None);

    stream->Write(input);
    assertEqual(stream->Length(), One);
    assertTrue(stream->GetMode() == SimpitStreamModeEnum::Write);

    assertTrue(stream->TryReadByte(output));
    assertEqual(stream->Length(), Zero);
    assertTrue(stream->GetMode() == SimpitStreamModeEnum::Read);
    assertEqual(input, output);

    stream->Clear();
    assertEqual(stream->Length(), Zero);
    assertTrue(stream->GetMode() == SimpitStreamModeEnum::None);
}

testF(SimpitStreamTests, read_write_bytes)
{
    FixedString input = FixedString("Hello World!");
    FixedString output;

    stream->Clear();
    assertEqual(stream->Length(), Zero);
    assertTrue(stream->GetMode() == SimpitStreamModeEnum::None);

    stream->Write(&input, sizeof(FixedString));
    assertEqual(stream->Length(), (unsigned int)sizeof(FixedString));
    assertTrue(stream->GetMode() == SimpitStreamModeEnum::Write);

    assertTrue(stream->TryReadBytes(sizeof(FixedString), &output));
    assertTrue(memcmp(&input, &output, sizeof(FixedString)) == Zero);
    assertEqual(input.Get(), output.Get());
    assertEqual(stream->Length(), Zero);
    assertTrue(stream->GetMode() == SimpitStreamModeEnum::Read);

    stream->Clear();
    assertEqual(stream->Length(), Zero);
    assertTrue(stream->GetMode() == SimpitStreamModeEnum::None);
}

testF(SimpitStreamTests, read_write_string)
{
    String input = F("Hello World!");
    String output = F("");

    stream->Clear();
    assertEqual(stream->Length(), (unsigned)0);
    assertTrue(stream->GetMode() == SimpitStreamModeEnum::None);

    stream->Write(input);
    assertEqual(stream->Length(), (int)sizeof(int) + input.length());
    assertTrue(stream->GetMode() == SimpitStreamModeEnum::Write);

    assertTrue(stream->TryReadString(&output));
    assertEqual(stream->Length(), Zero);
    assertTrue(stream->GetMode() == SimpitStreamModeEnum::Read);
    assertEqual(input, output);

    stream->Clear();
    assertEqual(stream->Length(), Zero);
    assertTrue(stream->GetMode() == SimpitStreamModeEnum::None);
}