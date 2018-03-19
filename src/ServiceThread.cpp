#include "ServiceThread.h"
#include <string>
#include "trojan/src/log.h"

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
  try {
    service->run();
  } catch (const std::exception &e) {
    Log::log_with_date_time(std::string("fatal: ") + e.what(), Log::FATAL);
  }
}
