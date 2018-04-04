/*
 * This file is part of the trojan project.
 * Trojan is an unidentifiable mechanism that helps you bypass GFW.
 * Copyright (C) 2018  Light Bob
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

#ifndef APP_H
#define APP_H

#define APP_DATA_DIR QStandardPaths::writableLocation(QStandardPaths::DataLocation)
#define SERVER_CONFIG_PATH APP_DATA_DIR + "/client.json"
#define CLIENT_CONFIG_PATH APP_DATA_DIR + "/server.json"
#define TROJAN_CONFIG_PATH APP_DATA_DIR + "/settings.json"

#include <QApplication>
#include <QStandardPaths>
#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <cstdlib>
#include <string>
#include "trojan/src/log.h"
#include "trojan/src/config.h"
#include "trojan/src/service.h"
#include "trojan/src/version.h"

#include "Window.h"


class App : public QApplication
{
  Q_OBJECT

public:
  App(int &argc, char **argv);
  ~App();

  Window *window;

  static QString client_config_path;
  static QString server_config_path;
  static Config::RunType current_run_type;

private:
  bool loadSettings();
  bool checkDir(const QString &dir);
  bool checkFile(const QString &path, const QString &populateDir);

};

#endif // APP_H
