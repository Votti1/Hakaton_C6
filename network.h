#ifndef NETWORK_H
#define NETWORK_H

void setupWiFi(void);
void sendDataToThingSpeak(float t_water, float t_oil, float fan_rpm, float pump_lpm);

#endif
