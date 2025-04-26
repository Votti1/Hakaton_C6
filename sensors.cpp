#include "sensors.h"
#include "config.h"

void setupSensors(void) {
  Serial.println(F("Initializing DHT sensors..."));
  dht_water.begin();
  dht_oil.begin();
  delay(100);
  Serial.println(F("DHT sensors initialized."));
}
