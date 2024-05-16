#include <Arduino.h>
#include <AUnit.h>
#include <FixedString.h>

using namespace aunit;

class FixedStringTests: public TestOnce
{
public:
    FixedString *value;

protected:
    void setup() override {
        TestOnce::setup();

        delete value;
    }

    void teardown() override {
        TestOnce::teardown();

        delete value;
    }
};

testF(FixedStringTests, set_under_buffer_get_equal)
{
    String input = F("Hello World! 12345");
    String output;

    value = new FixedString();

    value->Set(input);
    output = value->Get();

    assertEqual(input, output);
}

testF(FixedStringTests, set_over_buffer_get_trimmed)
{
    String input = F("Hello World! 123456789abcdefghijklmnopqrstuvwxyz");
    String output;

    value = new FixedString();
    
    value->Set(input);
    output = value->Get();

    assertEqual(output.length(), FixedString::BufferSize);
    assertEqual(input.substring(0, FixedString::BufferSize), output);
}