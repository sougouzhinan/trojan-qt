/*
 * This file is part of the trojan-gui project.
 * Trojan is an unidentifiable mechanism that helps you bypass GFW.
 * Copyright (C) 2018  GreaterFire
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
