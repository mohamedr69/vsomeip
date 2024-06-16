#ifndef ENGINE_H
#define ENGINE_H
#include <QDebug>
#include <QtCore/QCoreApplication>
#include <random>
class Engine {
 public:
  Engine();
  Engine(int oil, int temp, int RPM);
  std::string simulate_sensor_readings();
  int get_oil_level();
  int get_temp();
  int get_RPM();

 private:
  int oil_level;
  int temp;
  int RPM;
};

#endif  // ENGINE_H
