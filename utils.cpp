#include "utils.h"
#include "config.h"
#include <math.h>

void setupUtils() {
  pinMode(pin_rgb_r, OUTPUT);
  pinMode(pin_rgb_g, OUTPUT);
  SetColor(false, false);
}

float Clamp(float v, float v_min, float v_max) {
  return v < v_min ? v_min : (v > v_max ? v_max : v);
}

float CalcSlope(float t1, uint32_t ms1, float t2, uint32_t ms2) {
  if (isnan(t1) || isnan(t2)) {
    return 0.0f;
  }
  const float dt_seconds = static_cast<float>(ms2 - ms1) / 1000.0f;
  return dt_seconds > 0.0f ? (t2 - t1) / dt_seconds : 0.0f;
}

void SetColor(bool r, bool g) {
  digitalWrite(pin_rgb_r, r ? HIGH : LOW);
  digitalWrite(pin_rgb_g, g ? HIGH : LOW);
}

void BlinkFastRed(void) {
  for (uint8_t i = 0; i < 3; ++i) {
    SetColor(true, false);
    delay(200);
    SetColor(false, false);
    delay(200);
  }
}
