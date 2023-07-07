#include "Bee.h"
#include "NodeConfig.h"

#define DEBUG
#ifdef DEBUG
#define DEBUG_MSG(x) Serial.println(F(x))
#define DEBUG_MSG_VAR(x) Serial.println(x)
#else
#define DEBUG_MSG(x) // define empty, so macro does nothing
#define DEBUG_MSG_VAR(x)
#endif


/*!********************************************************************
 * @brief Construct a new Node:: Node object
 **********************************************************************/
Bee::Bee() :
    mTempHumidity(PIN_DHT22, DHT22),
    mBattery(PIN_POWER_MONITOR)
{
}

/**
* Function invoked by the node right after its own setup (as per Arduino Setup function)
* To be used for applicative setup
*/
void Bee::appSetup() {
    // set the Id of the node
    setNodeId(NODE_ID);
    setProcessingTimeInterval(PROCESSING_TIME_INTERVAL);
    setTransmissionTimeInterval(TRANSMISSION_TIME_INTERVAL);
    // ask for current state transmission
    setTransmissionNowFlag(true);

    //Initialize Temperature Humidity sensor
    mTempHumidity.begin();
}


/**
* Add JSON Tx payload messages
* @param payload the JSON payload to be completed as per application needs
*/
void Bee::addJsonTxPayload(JsonDocument& payload) {

    payload[MSG_HUMIDITY] = mTempHumidity.readHumidity();
    payload[MSG_TEMP] = mTempHumidity.readTemperature();
    mBattery.Run();
    payload[MSG_POWER] = mBattery.Get();
    serializeJson(payload, Serial);
}

/**
* Parse JSON Rx payload
* One should avoid any long processing in this routine. LoraNode::AppProcessing is the one to be used for this purpose
* Limit the processing to parsing the payload and retrieving the expected attributes
* @param payload the JSON payload received by the node
* return true in case of new message received
*/
bool Bee::parseJsonRxPayload(JsonDocument& payload) {
    return false;
}

/**
* App processing of the node.
* Invoke every loop of the nodes before Rx and Tx
* ONe should benefit from using processingTimeInterval to avoid overloading the node
*/
bool Bee::appProcessing() {
    return false;
}