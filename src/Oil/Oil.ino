#include <OneWire.h>
#include <DallasTemperature.h>

const int PIN_TEMP_IN  = 2;
const int PIN_TEMP_OUT = 3;

const float CP_OIL  = 1900.0;
const float RHO_OIL =  870.0;

float Q_load = 50000.0;

OneWire  oneWireIn (PIN_TEMP_IN);
OneWire  oneWireOut(PIN_TEMP_OUT);
DallasTemperature sensorsIn  (&oneWireIn);
DallasTemperature sensorsOut (&oneWireOut);

float Tin, Tout, dT;
float m_dot, Lpm;

void oilBegin(void) {
  sensorsIn.begin();
  sensorsOut.begin();
}

void oilReadTemps(void) {
  sensorsIn.requestTemperatures();
  sensorsOut.requestTemperatures();
  Tin  = sensorsIn.getTempCByIndex(0);
  Tout = sensorsOut.getTempCByIndex(0);
  dT   = Tout - Tin;
}

void oilCalculate(void) {
  if (dT <= 0.5) {
    m_dot = -1;
    Lpm   = -1;
  } else {
    m_dot = Q_load / (CP_OIL * dT);
    Lpm   = m_dot / RHO_OIL * 1000.0 * 60.0;
  }
}

float getTin(void) {
  return Tin;
}
float getTout(void) {
  return Tout;
}
float getDeltaT(void) {
  return dT;
}
float getMassFlow(void) {
  return m_dot;
}
float getVolumeFlow(void) {
  return Lpm;
}

