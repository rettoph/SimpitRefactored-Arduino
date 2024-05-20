#include <Arduino.h>
#include <AUnit.h>
#include <SimpitBuilder.h>
#include <SimpitMessageType.h>
#include <SimpitMacros.h>
#include <CheckSum.h>
#include <COBS.h>
#include <MemStream.h>

using namespace aunit;

class SimpitTests: public TestOnce
{
};

struct TestStruct
{
public:
    static TestStruct *Instance;

    int Value1;
    int Value2;
};

void TestStructCallback(void *sender, TestStruct* data)
{
    TestStruct::Instance->Value1 = TestStruct::Instance->Value2;
}

TestStruct* TestStruct::Instance = nullptr;
SIMPIT_DECLARE_INCOMING_TYPE(TestStruct, 123);

testF(SimpitTests, read_incoming_message)
{
    byte buffer[256];
    Stream* serial = new MemStream(buffer, 256, 0, true);

    Simpit* simpit = SimpitBuilder().RegisterIncoming<TestStruct>().RegisterCallback(TestStructCallback).Build(*serial);
    // Add some noise to the test struct
    TestStruct::Instance = new TestStruct();
    TestStruct::Instance->Value1 = 420;
    TestStruct::Instance->Value2 = 69;

    // Simulate and serialize an incoming message
    // 1. Write MessageTypeId byte
    // 2. Write message data
    // 3. Write Checksum
    // 4. COBS encode
    SimpitStream stream = SimpitStream();
    stream.Write(IncomingSimpitMessageType<TestStruct>::MessageTypeId);
    stream.Write(&TestStruct::Instance, sizeof(TestStruct));
    stream.Write(CheckSum::CalculateCheckSum(stream));
    assertTrue(COBS::TryEncode(stream));
    // Write the stream data to the simulated serial Stream
    byte incomingByte;
    while(stream.TryReadByte(incomingByte))
    {
        serial->write(incomingByte);
    }

    // Ensure test struct currently not equal
    assertNotEqual(TestStruct::Instance->Value1, TestStruct::Instance->Value2);

    // Publish "incoming" data
    int recieved = simpit->ReadIncoming();
    assertEqual(recieved, 1);

    // The custom subscriber above simply sets both values equal to each other.
    assertEqual(TestStruct::Instance->Value1, TestStruct::Instance->Value2);

    delete serial;
}

testF(SimpitTests, write_outgoing_message)
{
}