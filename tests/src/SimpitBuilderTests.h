#include <Arduino.h>
#include <AUnit.h>
#include <SimpitBuilder.h>
#include <SimpitMessageType.h>

using namespace aunit;

class SimpitBuilderTests: public TestOnce
{
public:
    SimpitBuilder *builder;

protected:
    void setup() override {
        TestOnce::setup();

        delete builder;
        builder = new SimpitBuilder();
    }

    void teardown() override {
        TestOnce::teardown();

        delete builder;
    }
};

struct TestStruct
{
public:
    int Value1;
    int Value2;
};

template class SimpitMessageType<TestStruct>;
template void SimpitBuilder::RegisterIncoming<TestStruct>(byte);

testF(SimpitBuilderTests, calculated_validates)
{
    this->builder->RegisterIncoming<TestStruct>((byte)24);
    this->builder->RegisterIncoming<TestStruct>((byte)27);
    BaseSimpitMessageType** types = this->builder->Build();

    TestStruct testStruct = TestStruct();
    testStruct.Value1 = 420;
    testStruct.Value2 = 69;

    types[0]->Publish(&testStruct);
    types[1]->Publish(&testStruct);
}