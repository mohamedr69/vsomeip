#ifndef ENGINE_H
#define ENGINE_H
const int MIN_OIL_LEVEL = 25;
const int MAX_OIL_LEVEL = 75;
const int MIN_OIL_TEMP = 82;
const int MAX_OIL_TEMP = 104;
const int MIN_IDLE_RPM = 600;
const int MAX_IDLE_RPM = 1000;
const int MAX_OPERATING_RPM = 4000;

class engine {
 public:
  engine();
  engine(int oil, int temp, int RPM);
  int get_oil_level();
  int get_temp();
  int getRPM();
  void set_oil(int oil);
  void set_temp(int temp);
  void set_RPM(int rpm);
  bool checkEngineCondition();

 private:
  int oil_level;
  int temp;
  int RPM;
};

#endif  // ENGINE_H
