#include <Arduino.h>
#include <AUnit.h>

#include "src/FixedStringTests.h"
#include "src/SimpitStreamTests.h"
#include "src/COBSTests.h"
#include "src/CheckSumTests.h"
#include "src/SerialPortTests.h"

using namespace aunit;

void setup() {
    Serial.begin(115200);
    while (! Serial); // Wait until Serial is ready - Leonardo/Micro
}

void loop() {
    TestRunner::run();
}