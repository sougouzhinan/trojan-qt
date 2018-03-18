#include "ServiceThread.h"

ServiceThread::ServiceThread(Config &config, QObject *parent) : QThread(parent) {
    service = new Service(config);
}

void ServiceThread::stop() {
    service->stop();
}

ServiceThread::~ServiceThread() {
    delete service;
}

void ServiceThread::run() {
    service->run();
}
