#include "engine.h"

Engine::Engine() {}
Engine::Engine(int oil, int temp, int RPM)
    : oil_level(oil), temp(temp), RPM(RPM) {}

std::string Engine::simulate_sensor_readings() {
  oil_level = std::rand() % 100 + 1;
  temp = std::rand() % 120 + 1;
  RPM = std::rand() % 7000 + 1;

  QString sensor_data = QString("%1,%2,%3").arg(oil_level).arg(temp).arg(RPM);
  // qDebug() << sensor_data;

  return sensor_data.toStdString();
}

int Engine::get_oil_level() { return oil_level; }
int Engine::get_temp() { return temp; }
int Engine::get_RPM() { return RPM; }
