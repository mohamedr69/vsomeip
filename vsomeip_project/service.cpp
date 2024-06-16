#include "service.h"
#define SERVICE_ID 0x0001
#define INSTANCE_ID 0x0001
#define METHOD_ID 0x0001
#define EVENT_ID 0x0001
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

#include "engine.h"
using json = nlohmann::json;

Service::Service(const std::string& config_file) {
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

  ifs.close();
  eng = new Engine();
  app = vsomeip::runtime::get()->create_application();
  QFuture<void> future = QtConcurrent::run([this, config]() {
    std::cout << "Initializing VSOMEIP...\n" << std::endl;
    app->init();
    app->offer_service(0x1234, 0x5678);
    app->register_message_handler(
        SERVICE_ID, INSTANCE_ID, METHOD_ID,
        [this](const std::shared_ptr<vsomeip::message>& _request) {
          on_message(_request);
        });
    app->offer_service(SERVICE_ID, INSTANCE_ID);
    // sendRequest();
    app->start();
  });
}
void Service::sendRequest() {
  auto request = vsomeip::runtime::get()->create_request();
  auto payload = vsomeip::runtime::get()->create_payload();
  std::vector<vsomeip::byte_t> payload_data;

  std::string text = "Hello from Server \n";
  payload_data.insert(payload_data.end(), text.begin(), text.end());
  payload->set_data(payload_data);
  request->set_payload(payload);
  request->set_service(SERVICE_ID);
  request->set_instance(INSTANCE_ID);
  request->set_method(METHOD_ID);
  app->send(request);
  std::cout << "Request sent \n";
}
void Service::on_message(const std::shared_ptr<vsomeip::message>& _request) {
  std::cout << "Clien request: \n";
  std::string data = eng->simulate_sensor_readings();
  auto response = vsomeip::runtime::get()->create_response(_request);
  auto payload = vsomeip::runtime::get()->create_payload();
  std::vector<vsomeip::byte_t> payload_data(data.begin(), data.end());
  payload->set_data(payload_data);
  response->set_payload(payload);
  app->send(response);
}
