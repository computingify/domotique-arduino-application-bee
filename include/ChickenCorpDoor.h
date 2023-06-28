#ifndef CHICKEN_CORP_DOOR_H
#define CHICKEN_CORP_DOOR_H

#include <ArduinoJson.h>
#include <Arduino.h>
#include <LoRaNode.h>
#include "actionner/HBridge.h"
#include "reader/AnalogInputFiltered.h"

class ChickenCorpDoor : public LoRaNode
{
public:
    ChickenCorpDoor();
    virtual ~ChickenCorpDoor() = default;

    void appSetup();
    virtual bool appProcessing() override;
    void addJsonTxPayload(JsonDocument& payload);
    virtual bool parseJsonRxPayload(JsonDocument& payload) override;

private:
    void commandRelay(uint8_t relay, uint8_t cmd);
    void parseJsonRelayCmd(uint8_t relay, char* cmd);

    AnalogInputFiltered mLux;
    HBridge mMotor;
};

#endif