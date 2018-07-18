#include "trojanthread.h"
#include <stdexcept>
#include "trojan/src/log.h"
using namespace std;

TrojanThread::TrojanThread(QObject *parent) : QThread(parent), service(nullptr) {}

void TrojanThread::cleanup() {
    if (service) {
        delete service;
        service = nullptr;
    }
}

void TrojanThread::startTrojan(const QString &configPath) {
    if (isRunning()) {
        emit trojanStarted();
        return;
    }
    cleanup();
    this->configPath = configPath;
    start();
}

void TrojanThread::stopTrojan() {
    if (!isRunning()) {
        return;
    }
    service->stop();
    wait();
    cleanup();
}

TrojanThread::~TrojanThread() {
    stopTrojan();
}

void TrojanThread::run() {
    try {
        Config config;
        config.load(configPath.toLocal8Bit().data());
        service = new Service(config);
        emit trojanStarted();
        service->run();
    } catch (const exception &e) {
        emit trojanFailed(e.what());
        Log::log_with_date_time(string("fatal: ") + e.what(), Log::FATAL);
    }
}
