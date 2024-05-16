#include <Arduino.h>
#include <AUnit.h>
#include <COBS.h>

using namespace aunit;

class COBSTests: public TestOnce
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

public:
    void TestEncodeDecodeMatchesInput(byte* input, unsigned int length)
    {
        stream->Clear();
        stream->Write((void*)input, length);

        assertTrue(COBS::TryEncode(*stream));
        assertTrue(COBS::TryDecode(*stream));
        assertEqual(stream->Length(), (unsigned int)length);

        byte value;
        for(int i = 0; i < length; i++)
        {
            assertTrue(stream->TryReadByte(value));
            assertEqual(input[i], value);
        }
    }
};

testF(COBSTests, decode_matches_encode_01)
{
    const unsigned int length = 9;
    byte *input = new byte[length] { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    TestEncodeDecodeMatchesInput(input, length);
}

testF(COBSTests, decode_matches_encode_02)
{
    const unsigned int length = 8;
    byte *input = new byte[length] { 0, 1, 0, 1, 0, 1, 0, 1 };

    TestEncodeDecodeMatchesInput(input, length);
}

testF(COBSTests, decode_matches_encode_03)
{
    const unsigned int length = 9;
    byte *input = new byte[length] { 0, 1, 2, 4, 8, 16, 32, 64, 128 };

    TestEncodeDecodeMatchesInput(input, length);
}

testF(COBSTests, decode_matches_encode_04)
{
    const unsigned int length = 9;
    byte *input = new byte[length] { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    TestEncodeDecodeMatchesInput(input, length);
}