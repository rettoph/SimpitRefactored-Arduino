/* KerbalSimpitHelloWorld
   A very barebones Hello World sketch, that doesn't require
   any extra hardware. It periodically sends EchoRequest packets
   to the game, and uses the EchoReply packets to switch the
   on-board LED on and off. Note that the game only activates the
   echo handler during the flight scene.
   Great for confirming basic connectivity.

   Peter Hardy <peter@hardy.dropbear.id.au>
*/
#include "Simpit.h"
#include "KerbalSimpit.h"

// Declare a KerbalSimpit object that will
// communicate using the "Serial" device.
// Allocate space for (1) message handler
Simpit mySimpit(1, Serial);

// This boolean tracks the desired LED state.
bool state = false;

// A timestamp of the last time we sent an echo packet.
unsigned long lastSent = 0;
// How often to send echo packets (in ms)
unsigned int sendInterval = 1000;

void setup() {
  // Open the serial connection.
  Serial.begin(115200);

  // Set up the built in LED, and turn it on.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  // This loop continually attempts to handshake with the plugin.
  // It will keep retrying until it gets a successful handshake.
  // 0x37 response value indicates KSP1
  byte initResponse;
  while(mySimpit.Init(initResponse) == false && initResponse != (byte)0x37)
  {
    delay(100);
  }
    
  // Turn off the built-in LED to indicate handshaking is complete.
  digitalWrite(LED_BUILTIN, LOW);
  // Display a message in KSP to indicate handshaking is complete.
  mySimpit.Log("Connected");
  // Sets our callback function. The KerbalSimpit library will
  // call this function every time a packet is received.
  mySimpit.RegisterIncomingHandler<EchoResponse>(EchoResponseHandler);
}

void loop() {
  unsigned long now = millis();
  // If we've waited long enough since the last message, send a new one.
  if (now - lastSent >= sendInterval) {
    // If the last message was "high", send "low"
    // and vice-versa.
    EchoRequest request = EchoRequest();
    
    if (state) {
      request.Write("low");
    } else {
      request.Write("high");
    }
    // Update when we last sent a message.
    lastSent = now;
    // Update the state variable to match the message we just sent.
    state = !state;
  }

  // Call the library update() function to check for new messages.
  mySimpit.Update();
}

void EchoResponseHandler(void *sender, EchoResponse *message)
{
  if (message->ReadString() == "low") {
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}
