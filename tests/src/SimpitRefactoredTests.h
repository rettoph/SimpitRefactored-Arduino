#include <Arduino.h>
#include <AUnit.h>
#include <SimpitRefactoredMessageType.h>
#include <SimpitRefactoredMacros.h>
#include <CheckSum.h>
#include <COBS.h>
#include <MemStream.h>
#include <KerbalSimpitRefactored.h>

using namespace aunit;

struct TestMessage
{
    static TestMessage Instance;

    int Value1;
    int Value2;
};

class SimpitTests: public TestOnce
{
public:
    
};

void TestMessagehandler(void *sender, TestMessage *data)
{
    TestMessage::Instance.Value1 = TestMessage::Instance.Value2;
}

TestMessage TestMessage::Instance = TestMessage();
SIMPIT_DECLARE_INCOMING_TYPE(TestMessage, 123);

testF(SimpitTests, read_incoming_message)
{
    byte buffer[256];
    Stream* serial = new MemStream(buffer, 256, 0, true);

    Simpit simpit(2, *serial);

    simpit.RegisterIncoming<TestMessage>(TestMessagehandler)
        .RegisterIncoming<TestMessage>(TestMessagehandler);

    // Add some noise to the test struct
    TestMessage::Instance.Value1 = 420;
    TestMessage::Instance.Value2 = 69;

    // Simulate and serialize an incoming message
    // 1. Write MessageTypeId byte
    // 2. Write message data
    // 3. Write Checksum
    // 4. COBS encode
    SimpitStream stream = SimpitStream();
    stream.Write(GenericIncomingSimpitMessageType<TestMessage>::MessageTypeId);
    stream.Write(&TestMessage::Instance, sizeof(TestMessage));
    stream.Write(CheckSum::CalculateCheckSum(stream));
    assertTrue(COBS::TryEncode(stream));
    // Write the stream data to the simulated serial Stream
    byte incomingByte;
    while(stream.TryReadByte(incomingByte))
    {
        serial->write(incomingByte);
    }

    // Ensure test struct currently not equal
    assertNotEqual(TestMessage::Instance.Value1, TestMessage::Instance.Value2);

    // Publish "incoming" data
    int recieved = simpit.ReadIncoming();
    assertEqual(recieved, 2);

    // The registered custom handler above simply sets both values equal to each other.
    assertEqual(TestMessage::Instance.Value1, TestMessage::Instance.Value2);

    delete serial;
}