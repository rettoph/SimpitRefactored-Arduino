#include <Arduino.h>
#include <AUnit.h>

#include "src/FixedStringTests.h"
#include "src/SimpitRefactoredStreamTests.h"
#include "src/COBSTests.h"
#include "src/CheckSumTests.h"
#include "src/SerialPortTests.h"
#include "src/SimpitRefactoredTests.h"

using namespace aunit;

void setup() {
    Serial.begin(115200);
    while (! Serial); // Wait until Serial is ready - Leonardo/Micro
}

void loop() {
    TestRunner::run();
}