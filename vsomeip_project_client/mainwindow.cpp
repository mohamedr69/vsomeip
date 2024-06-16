#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  c = new client("/home/mohamed/vsomeip_project_client/client.json");

  // eng = c->eng;
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_clicked() {
  c->sendRequest();
  if (c->eng->get_oil_level() == 0) {
    ui->label->setText("no connection");
    return;
  }
  int oil = c->eng->get_oil_level();
  int t = c->eng->get_temp();
  int r = c->eng->getRPM();
  std::string text = " Oil Level: " + std::to_string(c->eng->get_oil_level()) +
                     " ,Temperature : " + std::to_string(c->eng->get_temp()) +
                     "°C, RPM: " + std::to_string(c->eng->getRPM());
  QString qString = QString::fromStdString(text);
  ui->label->setText(qString);
  if (c->eng->checkEngineCondition()) {
    ui->label_2->setText("good condition");
  } else {
    ui->label_2->setText("needs maintenance");
  }
}
