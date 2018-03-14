#ifndef APP_H
#define APP_H

#include <QApplication>
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
};

#endif // APP_H
