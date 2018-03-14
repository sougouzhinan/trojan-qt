#include "App.h"
#include <QApplication>

#include <cstdlib>
#include <string>
#include "trojan/src/log.h"
#include "trojan/src/config.h"
#include "trojan/src/service.h"
#include "trojan/src/version.h"


using namespace std;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  App app;
  Log::log("Welcome to trojan " + Version::get_version(), Log::FATAL);
  if (argc != 2) {
      Log::log(string("usage: ") + argv[0] + " config_file", Log::FATAL);
      exit(1);
    }
  Config config;
  try {
    config.load(argv[1]);
    Service service(config);
    return service.run();
  } catch (const exception &e) {
    Log::log_with_date_time(string("fatal: ") + e.what(), Log::FATAL);
    Log::log_with_date_time("exiting. . . ", Log::FATAL);
    exit(1);
  }

  app.show();
  return a.exec();

}

