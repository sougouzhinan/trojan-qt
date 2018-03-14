#include "App.h"
#include <QApplication>

using namespace std;

int main(int argc, char *argv[]) {
  App app(argc, argv);
  app.window->show();
  return app.exec();
}

