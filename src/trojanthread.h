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

#ifndef TROJANTHREAD_H
#define TROJANTHREAD_H

#include <QThread>
#include <QString>
#include "trojan/src/service.h"

class TrojanThread : public QThread {
    Q_OBJECT
private:
    Service *service;
    QString configPath;
    void cleanup();
public:
    explicit TrojanThread(QObject *parent = 0);
    void startTrojan(const QString &configPath);
    void stopTrojan();
    ~TrojanThread();
protected:
    void run();
signals:
    void trojanStarted();
    void trojanFailed(QString errorMessage);
};

#endif // TROJANTHREAD_H
