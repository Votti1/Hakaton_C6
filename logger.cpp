#include "logger.h"

bool Logger::ready_ = false;

bool Logger::begin(void) {
  if (!LittleFS.begin()) {
    Serial.println(F("LittleFS init failed"));
    return false;
  }
  File f = LittleFS.open("/log.csv", "r");
  if (!f) {
    f = LittleFS.open("/log.csv", "w");
    if (f) {
      writeHeader_(f);
    }
  }
  ready_ = f;
  f.close();
  return ready_;
}

void Logger::writeHeader_(File &f) {
  f.println(F("ms,t_water,t_oil,fan_rpm,pump_lpm,dT_water,dT_oil"));
}

void Logger::log(uint32_t now_ms,
                 float t_water, float t_oil,
                 float fan_rpm, float pump_lpm,
                 float dT_water, float dT_oil) {
  if (!ready_) {
    return;
  }

  File f = LittleFS.open("/log.csv", "a");
  if (f) {
    f.printf("%lu,%.2f,%.2f,%.0f,%.2f,%.4f,%.4f\n", now_ms, t_water, t_oil, fan_rpm, pump_lpm, dT_water, dT_oil);
    f.close();
  }
  Serial.printf("LOG: %lu,%.2f,%.2f,%.0f,%.2f,%.4f,%.4f\n", now_ms, t_water, t_oil, fan_rpm, pump_lpm, dT_water, dT_oil);
}

