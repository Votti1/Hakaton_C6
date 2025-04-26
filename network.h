#ifndef NETWORK_H
#define NETWORK_H

void SetupWiFi(void);
void SendDataToThingSpeak(float t_water, float t_oil, float fan_rpm, float pump_lpm);

#endif
