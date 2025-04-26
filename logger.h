#pragma once
#include <Arduino.h>
#include <LittleFS.h>
#include <cstdint.h>

class Logger {
 public: 
  static bool begin(void);
  static void log(uint32_t now_ms,
                  float t_awter, float t_oil,
                  float fan_rpm, float pump_lpm,
                  float dT_water = NAN, float dT_oil = NAN);
 private:
  static void writeHeader_(File &f);
  static bool ready_;
};
