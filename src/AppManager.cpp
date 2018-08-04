#include "AppManager.h"

QJsonObject AppManager::client_config_obj;
QJsonObject AppManager::server_config_obj;
QString AppManager::client_config_path;
QString AppManager::server_config_path;
Config::RunType AppManager::current_run_type = Config::CLIENT;

bool AppManager::checkDir(const QString &dir)
{
  QDir d(dir);
  if(!d.exists())
    {
      if(!d.mkdir(dir))
        {
          Log::log_with_date_time("fail to check dir", Log::FATAL);

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
bool AppManager::checkFile(const QString &path, const QString &copy)
{
  QFile f(path);
  if(!f.exists())
    {
      if(!QFile::copy(copy, path))
        {
          Log::log_with_date_time(QString("Fail to copy " + copy + " to " + path).toStdString(), Log::FATAL);
          return false;
        }
      f.setPermissions(QFile::ReadOwner|QFile::WriteOwner|QFile::ExeOwner|QFile::ReadGroup|QFile::ExeGroup|QFile::ReadOther|QFile::ExeOther);
      Log::log_with_date_time(QString("copied " + copy + " to " + path).toStdString(), Log::INFO);
    }
  return true;
}

bool AppManager::loadJson(const QString &fileDir, QJsonObject &obj)
{
  QFile f(fileDir);
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

bool AppManager::writeJson(const QString &fileDir, QJsonObject &obj)
{
  QFile f(fileDir);
  if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      return false;
    }
  QJsonDocument doc;
  doc.setObject(obj);
  if(!f.write(doc.toJson()))
    {
      return false;
    }
  return true;
}

bool AppManager::loadAppConfig()
{
  QFile f(APP_CONFIG_PATH);
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
      AppManager::current_run_type = obj.value("current_mode").toString().toLower() == "client" ? Config::CLIENT : Config::SERVER;

      //! If the following if condition is not there, everything works
      //! but QString argument replacement error log is anoying.
      AppManager::client_config_path = obj.value("client_config").toString();
      if(AppManager::client_config_path.contains("%1"))
        {
          AppManager::client_config_path = AppManager::client_config_path.arg(APP_DATA_DIR);
        }
      AppManager::server_config_path = obj.value("server_config").toString();
      if(AppManager::server_config_path.contains("%1"))
        {
          AppManager::server_config_path = AppManager::server_config_path.arg(APP_DATA_DIR);
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
      AppManager::client_config_path = CLIENT_CONFIG_PATH;
      AppManager::server_config_path = SERVER_CONFIG_PATH;
      AppManager::current_run_type = Config::CLIENT;
    }
  return true;
}

bool AppManager::writeAppConfig()
{
  QFile f(APP_CONFIG_PATH);
  if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      Log::log_with_date_time("App::writeAppConfig() can't write", Log::FATAL);
      return false;
    }
  QTextStream stream(&f);

  QJsonObject obj;
  QString currentModeStr = (AppManager::current_run_type == Config::CLIENT) ? "client" : "server";
  obj.insert("current_mode", currentModeStr);
  obj.insert("client_config", AppManager::client_config_path);
  obj.insert("server_config", AppManager::server_config_path);

  QJsonDocument doc;
  doc.setObject(obj);

  stream << doc.toJson()<<endl;
  f.close();
  f.flush();

  return true;
}

bool AppManager::loadTrojanConfig()
{
  if(!AppManager::loadJson(AppManager::client_config_path, AppManager::client_config_obj))
    {
      if(!checkFile(AppManager::client_config_path, ":/file/file/client.json"))
        {
          Log::log_with_date_time(QString("Fail to copy :/file/file/client.json to " + AppManager::client_config_path).toStdString(), Log::FATAL);
          return false;
        }

      //! Second try
      if(!AppManager::loadJson(AppManager::client_config_path, AppManager::client_config_obj))
        {
          Log::log_with_date_time(QString("Fail to load " + AppManager::client_config_path).toStdString(), Log::FATAL);
          return false;
        }
    }

  if(!AppManager::loadJson(AppManager::server_config_path, AppManager::server_config_obj))
    {
      if(!checkFile(AppManager::server_config_path, ":/file/file/server.json"))
        {
          Log::log_with_date_time(QString("Fail to copy :/file/file/client.json to " + AppManager::server_config_path).toStdString(), Log::FATAL);
          return false;
        }

      //! Second try
      if(!AppManager::loadJson(AppManager::server_config_path, AppManager::server_config_obj))
        {
          Log::log_with_date_time(QString("Fail to load " + AppManager::server_config_path).toStdString(), Log::FATAL);
          return false;
        }
    }

  return true;
}

bool AppManager::writeTrojanConfig()
{
  if(!AppManager::writeJson(AppManager::client_config_path, AppManager::client_config_obj))
    {
      return false;
    }
  if(!AppManager::writeJson(AppManager::server_config_path, AppManager::server_config_obj))
    {
      return false;
    }
  return true;
}

void AppManager::setSystemProxy(const bool &enabled)
{
  if(enabled)
    {
#ifdef Q_OS_LINUX
      if(system("gsettings --version > /dev/null") == 0)
        {
          system(QString("gsettings set org.gnome.system.proxy.socks port %1").arg(client_config_obj["local_port"].toString("0")).toStdString().c_str());
          system(QString("gsettings set org.gnome.system.proxy.socks host %1").arg(client_config_obj["local_addr"].toString("0")).toStdString().c_str());
          system("gsettings set org.gnome.system.proxy ignore-hosts \"[]\"");
          system("gsettings set org.gnome.system.proxy mode \"manual\"");
        }
#endif
    }
  else
    {
#ifdef Q_OS_LINUX
      if(system("gsettings --version > /dev/null") == 0)
        {
          system(QString("gsettings set org.gnome.system.proxy.socks port 0").toStdString().c_str());
          system(QString("gsettings set org.gnome.system.proxy.socks host 0").toStdString().c_str());
          system("gsettings set org.gnome.system.proxy mode \"none\"");
        }
#endif
    }
}

void AppManager::popMessageBox(LogLevel l, QString info, QWidget *parent)
{
  QMessageBox *msgBox = new QMessageBox(parent);
  msgBox->setText(logLevelToString(l));
  msgBox->setInformativeText(info);
  msgBox->setFixedWidth(300);
  msgBox->exec();
}

QString AppManager::logLevelToString(AppManager::LogLevel l)
{
  QString r;
  switch (l) {
    case LogLevel::ALL:
      r.append("Trojan - All");
      break;
    case LogLevel::INFO:
      r.append("Trojan - Info");
      break;
    case LogLevel::WARN:
      r.append("Trojan - Warning");
      break;
    case LogLevel::ERROR:
      r.append("Trojan - Error");
      break;
    case LogLevel::FATAL:
      r.append("Trojan - Fatal");
      break;
    default:
      break;
    }
  return r;
}
