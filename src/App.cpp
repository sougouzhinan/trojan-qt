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

#include "App.h"

App::App(int &argc, char **argv)
  : QApplication(argc, argv)
  , window(new Window())
  , service(new ServiceThread(this))
{

#ifdef Q_OS_OSX
  QApplication::setQuitOnLastWindowClosed(false);
#endif

//  checkDir("/trojanTestFolder"); //Test root priv.

  checkDir(APP_DATA_DIR);
  checkFile(TROJAN_CONFIG_PATH, ":/file/file/settings.json");
  loadSettings();
  checkFile(Global::client_config_path, ":/file/file/client.json");
  checkFile(Global::server_config_path, ":/file/file/server.json");

  connect(service, &ServiceThread::started, window, &Window::onServerStarted);
  connect(service, &ServiceThread::exception, this, &App::popErrorBox);
  connect(window, &Window::startTriggered, this, &App::startTrojan);
}

App::~App()
{

}

bool App::loadSettings()
{
  if(!checkFile(TROJAN_CONFIG_PATH, ":/file/file/settings.json"))
    {
      return false;
    }
  QFile f(TROJAN_CONFIG_PATH);
  if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      return false;
    }

  QTextStream inStream(&f);
  QByteArray inByteArray = inStream.readAll().toUtf8();

  QJsonParseError jsonError;
  QJsonDocument inDoc = QJsonDocument::fromJson(inByteArray, &jsonError);
  if(jsonError.error == QJsonParseError::NoError && inDoc.isObject())
    {
      //! Read.
      QJsonObject obj = inDoc.object();
      Global::client_config_path = obj.value("client_config").toString().arg(APP_DATA_DIR);
      Global::server_config_path = obj.value("server_config").toString().arg(APP_DATA_DIR);
      Global::current_run_type = obj.value("current_mode").toString().toLower() == "client" ? Config::CLIENT : Config::SERVER;

      f.close();
      f.flush();
    }
  else
    {
      //! Mend.
      //! This is not the perfect way to do it, but it works well.
      //! Because it enters default settings by code instead of reading from the file.
      //! When the config file is getting more complicated, it brings inconvenience to the development.
      f.close();
      f.flush();

      if(!QFile::copy(TROJAN_CONFIG_PATH, ":/file/file/settings.json"))
        {
          return false;
        }
      Global::client_config_path = CLIENT_CONFIG_PATH;
      Global::server_config_path = SERVER_CONFIG_PATH;
      Global::current_run_type = Config::CLIENT;
    }
  return true;
}

bool App::checkDir(const QString &dir)
{
  QDir d(dir);
  if(!d.exists())
    {
      if(!d.mkdir(dir))
        {
          return false;
        }
    }
  return true;
}

bool App::checkFile(const QString &path, const QString &populateDir)
{
  QFile f(path);
  if(!f.exists())
    {
      if(!QFile::copy(populateDir, path))
        {
          Log::log_with_date_time(QString("Fail to copy " + populateDir + " to " + path).toStdString(), Log::FATAL);
          return false;
        }
      Log::log_with_date_time(QString("copied " + populateDir + " to " + path).toStdString(), Log::INFO);
    }
  return true;
}

void App::startTrojan()
{
  service->config().load(Global::current_run_type == Config::CLIENT ?
                             Global::client_config_path.toStdString() : Global::server_config_path.toStdString());
  service->start();
}

void App::popErrorBox(const QString &what)
{
  window->onServerStarted(false);
  Global::popMessageBox(Global::ERROR, what, window);

}
