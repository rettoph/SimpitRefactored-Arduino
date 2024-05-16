#include <Arduino.h>
#include <AUnit.h>
#include <CheckSum.h>

using namespace aunit;

class CheckSumTests: public TestOnce
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

testF(CheckSumTests, calculated_validates)
{
    const unsigned int length = 9;
    byte *data = new byte[length] { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        stream->Clear();
        stream->Write((void*)data, length);

        byte checksum = CheckSum::CalculateCheckSum(*stream);
        stream->Write(checksum);

        assertTrue(CheckSum::ValidateCheckSum(*stream));
}