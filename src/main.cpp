#include <Arduino.h>
#include <ArduinoJson.h>
#include <LoRa.h>
#include <LoRaHomeNode.h>
#include <LowPower.h>
#include <SPI.h>
#include "Bee.h"
#include "LowPower.h"

// #define DEBUG

#ifdef DEBUG
#define DEBUG_MSG(x) Serial.println(F(x))
#define DEBUG_MSG_VAR(x) Serial.println(x)
#else
#define DEBUG_MSG(x) // define empty, so macro does nothing
#endif

// Objects instentiation
Bee mNode;
LoRaHomeNode mLoRaHome(mNode);

// sampling management
unsigned long lastSendTime = 0;    // last send time
unsigned long lastProcessTime = 0; // last processing time

void goToSleep() {
  digitalWrite(LED_BUILTIN, LOW);

  // Serial.println("\nArduino:- Go to sleep");
  delay(500);
  LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);

  digitalWrite(LED_BUILTIN, HIGH);

  delay(2000);  // time driver to go back in run mode
  // Serial.println("Arduino:- Hey I just Woke up");
  // Serial.println("");
}

void setup()
{

  //initialize Serial Monitor
#ifdef DEBUG
  Serial.begin(115200);
  while (!Serial)
    ;
  DEBUG_MSG("initializing LoRa Node");
#endif
  // initialize LoRa    
  mLoRaHome.setup();
  // call node specific configuration (end user)
  mNode.appSetup();

  mLoRaHome.sendToGateway();
  lastSendTime = millis(); // timestamp the message
}

/**
* Main loop of the LoRa Node
* Constantly try to receive JSON LoRa message
* Every transmissionTimeInterval send JSON LoRa messages
*/
void loop()
{
  unsigned long tick = millis();

  // Send Task
  if ((tick - lastSendTime) > mNode.getTransmissionTimeInterval()) {
    mLoRaHome.sendToGateway();
    lastSendTime = millis(); // timestamp the message
  }

  goToSleep(); // during 10.5s
  // delay(3000);
}
