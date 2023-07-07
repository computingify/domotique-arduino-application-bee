#ifndef NODE_CONFIG_H
#define NODE_CONFIG_H

const uint8_t NODE_ID = 3;
const unsigned long PROCESSING_TIME_INTERVAL = 10000;
const unsigned long TRANSMISSION_TIME_INTERVAL = 3000;
const uint16_t MY_NETWORK_ID = 0xACDC;

// Jeedom Message
#define MSG_TEMP "temp"
#define MSG_HUMIDITY "hum"
#define MSG_POWER "pow"

#define PIN_DHT22 A5
#define PIN_POWER_MONITOR A2
#endif 