#include "Global.h"

QString Global::client_config_path;
QString Global::server_config_path;
Config::RunType Global::current_run_type;

void Global::popMessageBox(LogLevel l, QString info, QWidget *parent)
{
  QMessageBox *msgBox = new QMessageBox(parent);
  msgBox->setText(logLevelToString(l));
  msgBox->setInformativeText(info);
  msgBox->setFixedWidth(300);
  msgBox->exec();
}

QString Global::logLevelToString(Global::LogLevel l)
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
