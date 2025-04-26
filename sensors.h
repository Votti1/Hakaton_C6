#ifndef SENSORS_H
#define SENSORS_H

#include <DHT.h>

extern DHT dht_water;
extern DHT dht_oil;

void SetupSensors(void);

#endif
