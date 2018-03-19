#include "TrojanService.h"
#include "trojan/src/log.h"

TrojanService::TrojanService(QObject *parent) :
  QObject(parent),
  thread(nullptr),
  _config(new Config()) {}

Config& TrojanService::config() {
  return *_config;
}

TrojanService::~TrojanService() {
  if (started()) {
    stop();
  }
  delete _config;
}

void TrojanService::start() {
  if (started()) {
    return;
  }
  Log::level = _config->log_level;
  thread = new ServiceThread(*_config, this);
  thread->start();
}

bool TrojanService::started() {
  return thread != nullptr;
}

void TrojanService::stop() {
  if (!started()) {
    return;
  }
  thread->stop();
  thread->wait();
  delete thread;
  thread = nullptr;
  delete _config;
  _config = new Config();
}
