#include "mainwindow.h"

#include <QTimer>

#include "./ui_mainwindow.h"
using json = nlohmann::json;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  s = new Service("/home/mohamed/vsomeip_project/service.json");
  timer = new QTimer();
  ui->setupUi(this);
  s->eng->simulate_sensor_readings();
  update();
  connect(timer, &QTimer::timeout, this, &MainWindow::update);
  int interval = 500;
  timer->setInterval(interval);
  timer->start();
}

void MainWindow::update() {
  std::string text = " Oil Level: " + std::to_string(s->eng->get_oil_level()) +
                     " ,Temperature : " + std::to_string(s->eng->get_temp()) +
                     "°C, RPM: " + std::to_string(s->eng->get_RPM());
  QString qString = QString::fromStdString(text);
  ui->label_2->setText(qString);
}
MainWindow::~MainWindow() { delete ui; }
