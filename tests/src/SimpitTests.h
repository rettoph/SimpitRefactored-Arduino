#include <Arduino.h>
#include <AUnit.h>
#include <SimpitBuilder.h>
#include <SimpitMessageType.h>
#include <SimpitMacros.h>
#include <CheckSum.h>
#include <COBS.h>
#include <MemStream.h>
#include <KerbalSimpitAddon.h>

using namespace aunit;

struct TestMessage
{
public:
    int Value1;
    int Value2;
};

class SimpitTests: public TestOnce
{
public:
    TestMessage* data;
};


SIMPIT_DECLARE_INCOMING_TYPE(TestMessage, 123);

testF(SimpitTests, read_incoming_message)
{
    byte buffer[256];
    Stream* serial = new MemStream(buffer, 256, 0, true);

    Simpit* simpit = SimpitBuilder().RegisterAddon(new KerbalSimpitAddon()).RegisterIncoming<TestMessage>()
        .RegisterIncomingHandler<TestMessage>([this](void *sender, TestMessage *data) {
            assertNotEqual(this->data->Value1, this->data->Value2);

            this->data->Value1 = this->data->Value2;

            assertEqual(this->data->Value1, this->data->Value2);
        })
        .Build(*serial);

    // Add some noise to the test struct
    this->data = new TestMessage();
    this->data->Value1 = 420;
    this->data->Value2 = 69;

    // Simulate and serialize an incoming message
    // 1. Write MessageTypeId byte
    // 2. Write message data
    // 3. Write Checksum
    // 4. COBS encode
    SimpitStream stream = SimpitStream();
    stream.Write(GenericIncomingSimpitMessageType<TestMessage>::MessageTypeId);
    stream.Write(&this->data, sizeof(TestMessage));
    stream.Write(CheckSum::CalculateCheckSum(stream));
    assertTrue(COBS::TryEncode(stream));
    // Write the stream data to the simulated serial Stream
    byte incomingByte;
    while(stream.TryReadByte(incomingByte))
    {
        serial->write(incomingByte);
    }

    // Ensure test struct currently not equal
    assertNotEqual(this->data->Value1, this->data->Value2);

    // Publish "incoming" data
    int recieved = simpit->ReadIncoming();
    assertEqual(recieved, 1);

    // The custom handler above simply sets both values equal to each other.
    assertEqual(this->data->Value1, this->data->Value2);

    delete serial;
}