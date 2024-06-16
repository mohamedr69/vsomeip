#ifndef VSOMEIPINITIALIZER_H
#define VSOMEIPINITIALIZER_H
#include <QThread>
#include <QCoreApplication>
#include <iostream>
#include <QThread>
#include <QCoreApplication>
#include <iostream>

class VSOMEIPInitializer : public QObject {
    Q_OBJECT

public:
    explicit VSOMEIPInitializer(QObject *parent = nullptr) : QObject(parent) {}

public slots:
    void initializeVSOMEIP() {

        std::cout << "Initializing VSOMEIP..." << std::endl;
        app->start(); // Assuming 'app' is the VSOMEIP application object
        std::cout << "VSOMEIP initialized." << std::endl;
    }
};

class InitializationThread : public QThread {
    Q_OBJECT

public:
    explicit InitializationThread(QObject *parent = nullptr) : QThread(parent) {}

protected:
    void run() override {
        VSOMEIPInitializer initializer;

        initializer.moveToThread(QCoreApplication::instance()->thread());

        connect(this, &InitializationThread::startInitialization, &initializer, &VSOMEIPInitializer::initializeVSOMEIP);

        emit startInitialization();
    }
};

#endif // VSOMEIPINITIALIZER_H
