#ifndef CLIENT_H
#define CLIENT_H
#include <QtCore/QCoreApplication>
#include <iostream>
#include <vsomeip/vsomeip.hpp>

#include "engine.h"
class client {
 public:
  client();
  std::shared_ptr<engine> eng;
  void sendRequest();
  void run();
  void on_state(vsomeip::state_type_e state);

 private:
  void on_message(const std::shared_ptr<vsomeip::message>& _request);
  std::shared_ptr<vsomeip::application> app;
};

#endif  // CLIENT_H
