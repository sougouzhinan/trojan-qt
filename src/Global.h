#ifndef GLOBAL_H
#define GLOBAL_H

#include "trojan/src/config.h"
#include "QString"
#include "QMessageBox"

class Global
{
public:
  enum LogLevel {
      ALL = 0,
      INFO = 1,
      WARN = 2,
      ERROR = 3,
      FATAL = 4,
      OFF = 5
  };

  static QString client_config_path;
  static QString server_config_path;
  static Config::RunType current_run_type;

  static void popMessageBox(LogLevel l, QString info, QWidget *parent);

  static QString logLevelToString(LogLevel l);
};

#endif // GLOBAL_H
