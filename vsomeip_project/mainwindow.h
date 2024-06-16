#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <vsomeip/vsomeip.hpp>

#include "engine.h"
#include "service.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  void display_engine();
  ~MainWindow();
 private slots:
  void update();

 private:
  Ui::MainWindow *ui;
  Service *s;
  std::shared_ptr<vsomeip::application> app;
  QTimer *timer;
};
#endif  // MAINWINDOW_H
