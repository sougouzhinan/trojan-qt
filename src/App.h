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



#include <QApplication>
#include <QMessageBox>
#include <cstdlib>
#include <string>
#include "trojan/src/log.h"
#include "trojan/src/config.h"
#include "trojan/src/service.h"
#include "trojan/src/version.h"

#include "Window.h"
#include "ServiceThread.h"



class App : public QApplication
{
  Q_OBJECT

public:
  App(int &argc, char **argv);
  ~App();

  static void popMessageBox(QString msg, QString info);

  Window *window;

private:
  ServiceThread *service;

private slots:
  void startTrojan();
  void stopTrojan();
  void popErrorBox(const QString &what);

};

#endif // APP_H
