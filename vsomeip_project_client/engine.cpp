#include "engine.h"

engine::engine() {}
engine::engine(int oil, int temp, int RPM)
    : oil_level(oil), temp(temp), RPM(RPM) {}
int engine::get_oil_level() { return oil_level; }
int engine::get_temp() { return temp; }
int engine::getRPM() { return RPM; }
void engine::set_oil(int oil) { oil_level = oil; }
void engine::set_temp(int temp) { this->temp = temp; }
void engine::set_RPM(int rpm) { RPM = rpm; }
bool engine::checkEngineCondition() {
  bool condition = true;
  bool isOilLevelNormal =
      (oil_level >= MIN_OIL_LEVEL) && (oil_level <= MAX_OIL_LEVEL);
  bool isOilNormal = (temp >= MIN_OIL_TEMP) && (temp <= MAX_OIL_TEMP);
  bool isRPMNormal = (RPM >= MIN_IDLE_RPM) && (RPM <= MAX_IDLE_RPM);

  if (!isOilLevelNormal) {
    condition = false;
  }

  if (!isOilNormal) {
    condition = false;
  }

  if (!isRPMNormal) {
    condition = false;
  }
  return condition;
}
