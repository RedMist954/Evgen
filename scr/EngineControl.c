#include "EngineControl.h"
#include "Arduino.h"

E_control::E_control(int new_CONTROL_PIN, int new_GRIN_PIN, unsigned long new_dt, bool new_mode, double new_R, double new_turnoverTick):CONTROL_PIN(new_CONTROL_PIN), GRIN_PIN(new_GRIN_PIN), _dt(new_dt), _mode(new_mode), R(new_R), turnoverTick(new_turnoverTick) {}

void E_control::scoreTickes() {
  if(!_mode || (digitalRead(GRIN_PIN) == HIGH)) {
    ++tickes;
  }
  else {
    --tickes;
  }
}

double E_control::angleSpeedCalc() {
  long real_dt = micros() - engineTimer;
  if (real_dt >= _dt) {                      // потенциальная проблема
    engineTimer = micros();
    noInterrupts();
    long CopyTickes = tickes;
    interrupts();
    angleSpeed = ((double)CopyTickes - lastTickes) / turnoverTick * 2 * 3.14 * 1000 * 1000 / real_dt;
    lastTickes = CopyTickes;
    return angleSpeed;
}
  else {
    return angleSpeed;
  }
}

double E_control::distansCalc() {
  distans = (double)tickes / turnoverTick * 2 * 3.14 * R;
  return distans;
}

double E_control::linearSpeedCalc() {
  double localangleSpeed = E_control::angleSpeedCalc();
  linearSpeed = localangleSpeed * R;
  return linearSpeed;
}

void E_control::PWM_Control(double reqest) {
  int finalSpeed = map(reqest, 0, 26, 0, 255);
  analogWrite(CONTROL_PIN, finalSpeed);
}

