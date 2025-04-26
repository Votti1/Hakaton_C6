#include <ESP8266WiFi.h>
#include <DHT.h>
#include <math.h>

#include "config.h"
#include "utils.h"
#include "control.h"
#include "network.h"
#include "sensors.h"

DHT dht_water(pin_dht_water, DHT11);
DHT dht_oil(pin_dht_oil, DHT11);

uint32_t prev_read_ms = 0;
uint32_t prev_push_ms = 0;
float    prev_water   = NAN;
float    prev_oil     = NAN;

void setup() {
  Serial.begin(9600);
  Serial.println(F("\n\nTemperature Monitor Starting..."));

  setupUtils();
  setupSensors();
  setupWiFi();

  prev_read_ms = millis();
  prev_push_ms = millis();

  Serial.println(F("Setup complete. Starting main loop."));
}

void loop() {
  const uint32_t now = millis();

  if (now - prev_read_ms >= read_every_ms) {
    float t_water = dht_water.readTemperature();
    float t_oil   = dht_oil.readTemperature();

    if (isnan(t_water) || isnan(t_oil)) {
      Serial.println(F("Error reading from DHT sensor!"));
      SetColor(true, true);
    } else {
      const float dT_water = CalcSlope(prev_water, prev_read_ms, t_water, now);
      const float dT_oil   = CalcSlope(prev_oil,   prev_read_ms, t_oil,   now);
      const float hottest  = max(t_water, t_oil);

      const float fan_rpm  = ComputeFanRpm(hottest);
      const float pump_lpm = ComputePumpLpm(hottest);

      Serial.printf("Water: %.1f°C | Oil: %.1f°C | Fan: %.0f RPM | Pump: %.1f L/min | dTw: %.3f°C/s | dTo: %.3f°C/s\n",
                    t_water, t_oil, fan_rpm, pump_lpm, dT_water, dT_oil);

      if (hottest >= temp_crit) {
        BlinkFastRed();
      } else if (hottest >= temp_norm) {
        SetColor(true, false);
      } else {
        SetColor(false, true);
      }

      prev_water   = t_water;
      prev_oil     = t_oil;
      prev_read_ms = now;

      if (WiFi.status() == WL_CONNECTED && (now - prev_push_ms >= push_every_ms)) {
         sendDataToThingSpeak(t_water, t_oil, fan_rpm, pump_lpm);
         prev_push_ms = now;
      }
    }
  }
  delay(10);
}
