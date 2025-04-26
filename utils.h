#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

float Clamp(float v, float v_min, float v_max);
float CalcSlope(float t1, uint32_t ms1, float t2, uint32_t ms2);
void SetColor(bool r, bool g);
void BlinkFastRed(void);
void SetupUtils(void);

#endif
