#ifndef SERVICE_H
#define SERVICE_H
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vsomeip/vsomeip.hpp>

#include "engine.h"
class Service {
 public:
  Service();
  Service(const std::string& config_file);
  void start();
  Engine* eng;
  void sendRequest();

 private:
  void on_message(const std::shared_ptr<vsomeip::message>& _request);

  std::shared_ptr<vsomeip::application> app;
};

#endif  // SERVICE_H
