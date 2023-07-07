#ifndef BEE_H
#define BEE_H

#include <ArduinoJson.h>
#include <Arduino.h>
#include <LoRaNode.h>
#include "reader/DHT/DHT.h"
#include "reader/BatteryMonitor.h"

class Bee : public LoRaNode
{
public:
    Bee();
    virtual ~Bee() = default;

    virtual void appSetup() override;
    virtual bool appProcessing() override;
    virtual void addJsonTxPayload(JsonDocument& payload) override;
    virtual bool parseJsonRxPayload(JsonDocument& payload) override;

private:
    void parseJsonRelayCmd(uint8_t relay, char* cmd);

    DHT mTempHumidity;
    BatteryMonitor mBattery;
};

#endif