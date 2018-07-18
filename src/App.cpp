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
  checkFile(APP_CONFIG_PATH, ":/file/file/settings.json");
  loadAppConfig();
  if(loadTrojanConfig())
    {

    }

  connect(service, &ServiceThread::exception, this, &App::popErrorBox);
  connect(service, &ServiceThread::started, window, &Window::onServerStarted);
  connect(window, &Window::startTriggered, this, &App::startTrojan);

  window->setCurrentMode(Global::current_run_type);
}

App::~App()
{
  writeAppConfig();
  Log::log_with_date_time("Exit", Log::INFO);
}

bool App::loadAppConfig()
{
  QFile f(APP_CONFIG_PATH);
  f.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
  if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      return false;
    }
  QByteArray byteArray = f.readAll();
  f.close();
  f.flush();

  QJsonParseError jsonErr;
  QJsonDocument doc = QJsonDocument::fromJson(byteArray, &jsonErr);
  if(jsonErr.error == QJsonParseError::NoError && doc.isObject())
    {
      //! Read.
      QJsonObject obj = doc.object();
      Global::current_run_type = obj.value("current_mode").toString().toLower() == "client" ? Config::CLIENT : Config::SERVER;

      //! If the following if condition is not there, everything works
      //! but QString argument replacement error log is anoying.
      Global::client_config_path = obj.value("client_config").toString();
      if(Global::client_config_path.contains("%1"))
        {
          Global::client_config_path = Global::client_config_path.arg(APP_DATA_DIR);
        }
      Global::server_config_path = obj.value("server_config").toString();
      if(Global::server_config_path.contains("%1"))
        {
          Global::server_config_path = Global::server_config_path.arg(APP_DATA_DIR);
        }
    }
  else
    {
      //! Mend.
      //! This is not the perfect way to do it, but it works well.
      //! Because it enters default settings by code instead of reading from the file.
      //! When the config file is getting more complicated, it brings inconvenience to the development.
      if(!QFile::copy(APP_CONFIG_PATH, ":/file/file/settings.json"))
        {
          return false;
        }
      Global::client_config_path = CLIENT_CONFIG_PATH;
      Global::server_config_path = SERVER_CONFIG_PATH;
      Global::current_run_type = Config::CLIENT;
    }
  return true;
}

bool App::writeAppConfig()
{
  QFile f(APP_CONFIG_PATH);
  if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      qDebug()<<"read file fatal"<<f.errorString();
      return false;
    }
  QTextStream stream(&f);

  QJsonObject obj;
  QString currentModeStr = (Global::current_run_type == Config::CLIENT) ? "client" : "server";
  obj.insert("current_mode", currentModeStr);
  obj.insert("client_config", Global::client_config_path);
  obj.insert("server_config", Global::server_config_path);

  QJsonDocument doc;
  doc.setObject(obj);

  stream << doc.toJson()<<endl;
  f.close();
  f.flush();

  return true;
}

bool App::loadTrojanConfig()
{
  if(!loadJson(Global::client_config_path, Global::client_config_obj))
    {
      if(!checkFile(Global::client_config_path, ":/file/file/client.json"))
        {
          Log::log_with_date_time(QString("Fail to copy :/file/file/client.json to " + Global::client_config_path).toStdString(), Log::FATAL);
          return false;
        }

      //! Second try
      if(!loadJson(Global::client_config_path, Global::client_config_obj))
        {
          Log::log_with_date_time(QString("Fail to load " + Global::client_config_path).toStdString(), Log::FATAL);
          return false;
        }
    }

  if(!loadJson(Global::server_config_path, Global::server_config_obj))
    {
      if(!checkFile(Global::server_config_path, ":/file/file/server.json"))
        {
          Log::log_with_date_time(QString("Fail to copy :/file/file/client.json to " + Global::server_config_path).toStdString(), Log::FATAL);
          return false;
        }

      //! Second try
      if(!loadJson(Global::server_config_path, Global::server_config_obj))
        {
          Log::log_with_date_time(QString("Fail to load " + Global::server_config_path).toStdString(), Log::FATAL);
          return false;
        }
    }

  return true;
}

bool App::loadJson(const QString &fileDir, QJsonObject &obj)
{
  QFile f(fileDir);
  f.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
  if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      return false;
    }

  QByteArray byteArray = f.readAll();
  f.close();
  f.flush();

  QJsonParseError jsonErr;
  QJsonDocument doc = QJsonDocument::fromJson(byteArray, &jsonErr);
  if(jsonErr.error == QJsonParseError::NoError && doc.isObject())
    {
      obj = doc.object();
      return true;
    }
  else
    {
      return false;
    }
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

/*!
 * \brief App::checkFile
 * \param path The path of the file to check.
 * \param copy If the file is broken or doesn't exist, copy file from path "copy" to "path".
 * \return successful
 */
bool App::checkFile(const QString &path, const QString &copy)
{
  QFile f(path);
  if(!f.exists())
    {
      if(!QFile::copy(copy, path))
        {
          Log::log_with_date_time(QString("Fail to copy " + copy + " to " + path).toStdString(), Log::FATAL);
          return false;
        }
      Log::log_with_date_time(QString("copied " + copy + " to " + path).toStdString(), Log::INFO);
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
