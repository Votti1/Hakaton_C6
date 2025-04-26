#include "control.h"
#include "config.h"
#include "utils.h"
#include <math.h>

float ComputeFanRpm(float hottest_temp) {
  const float delta = std::max(0.0f, hottest_temp - temp_norm);
  const int   steps = static_cast<int>(delta / 5.0f);
  const float set_rps = rpm_min / 60.0f + steps * fan_rps_per_5deg;
  return Clamp(set_rps * 60.0f, rpm_min, rpm_max);
}

float ComputePumpLpm(float hottest_temp) {
  const float delta = std::max(0.0f, hottest_temp - temp_norm);
  const int   steps = static_cast<int>(delta / 5.0f);
  const float set_lps = lpm_min / 60.0f + steps * pump_lps_per_5deg;
  return Clamp(set_lps * 60.0f, lpm_min, lpm_max);
}
