#include "client.h"

#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <condition_variable>
#include <iostream>
#include <thread>
std::mutex mutex;
std::condition_variable condition;
using json = nlohmann::json;

#define SERVICE_ID 0x0001
#define INSTANCE_ID 0x0001
#define METHOD_ID 0x0001
#define EVENT_ID 0x0001
void on_availability(vsomeip::service_t _service, vsomeip::instance_t _instance,
                     bool is_available) {
  if (is_available) {
    std::cout << "service " << _service << " instance " << _instance
              << " is available \n";

  } else {
    std::cout << "service " << _service << " instance " << _instance
              << " is NOT  available\n";
  }
  condition.notify_one();
}
client::client(const std::string& config_file)
    : eng(std::make_shared<engine>(0, 0, 0)) {
  std::ifstream ifs(config_file);
  if (!ifs.is_open()) {
    std::cerr << "Failed to open configuration file: " << config_file
              << std::endl;
    return;
  }

  json config;
  try {
    ifs >> config;
  } catch (const json::parse_error& e) {
    std::cerr << "Failed to parse configuration file: " << e.what()
              << std::endl;
    return;
  }
  app = vsomeip::runtime::get()->create_application("Client");
  QFuture<void> future = QtConcurrent::run([this, config]() {
    std::cout << "Initializing VSOMEIP...\n" << std::endl;
    app->init();

    app->request_service(SERVICE_ID, INSTANCE_ID);
    app->register_state_handler(
        std::bind(&client::on_state, this, std::placeholders::_1));
    app->register_message_handler(
        SERVICE_ID, INSTANCE_ID, METHOD_ID,
        [this](const std::shared_ptr<vsomeip::message>& _request) {
          std::cout << "here respond: \n";
          qDebug() << "here respond:\n";
          on_message(_request);
        });
    std::cout << "before request \n";

    app->start();

    std::cout << "VSOMEIP initialized.\n" << std::endl;
  });

  // Send a request message
}
void client::on_state(vsomeip::state_type_e state) {
  if (state == vsomeip::state_type_e::ST_REGISTERED) {
    auto message = vsomeip::runtime::get()->create_request();
    message->set_service(SERVICE_ID);
    message->set_instance(INSTANCE_ID);
    message->set_method(METHOD_ID);
    app->send(message);
    qDebug() << "Sent diagnostic request.";
  }
}
void client::sendRequest() {
  std::cout << "Request\n";

  auto request = vsomeip::runtime::get()->create_request();
  auto payload = vsomeip::runtime::get()->create_payload();
  std::vector<vsomeip::byte_t> payload_data;

  std::string text = "Hello from client \n";
  payload_data.insert(payload_data.end(), text.begin(), text.end());
  payload->set_data(payload_data);
  request->set_payload(payload);
  request->set_service(SERVICE_ID);
  request->set_instance(INSTANCE_ID);
  request->set_method(METHOD_ID);
  app->send(request);
  std::cout << "Request sent \n";
}
void client::run() {
  std::cout << "run\n";
  std::unique_lock<std::mutex> lock(mutex);
  condition.wait(lock);
  sendRequest();
}
void client::on_message(const std::shared_ptr<vsomeip::message>& response) {
  std::cout << "Server respond: \n";
  auto payload = response->get_payload();
  auto payload_data = payload->get_data();
  auto payload_length = payload->get_length();

  std::string data(reinterpret_cast<const char*>(payload_data), payload_length);

  QStringList sensorReadings = QString::fromStdString(data).split(',');
  qDebug() << sensorReadings;

  QString oilLevel = sensorReadings[0];
  QString temperature = sensorReadings[1];
  QString rpm = sensorReadings[2];
  // qDebug() << oilLevel;
  int oil = sensorReadings[0].toInt();
  int t = sensorReadings[1].toInt();
  int r = sensorReadings[2].toInt();
  qDebug() << r;

  eng->set_oil(oil);
  eng->set_temp(t);
  eng->set_RPM(r);
}
