#include "App.h"

App::App(int &argc, char **argv)
  : QApplication(argc, argv)
  , window(new Window())
{
#ifdef Q_OS_OSX
  QApplication::setQuitOnLastWindowClosed(false);
#endif

//  Log::log("Welcome to trojan " + Version::get_version(), Log::FATAL);
//  if (argc != 2) {
//      Log::log(std::string("usage: ") + argv[0] + " config_file", Log::FATAL);
//      //    exit(1);
//      //! GUI
//    }

//  Config config;
//  try {
//    config.load(argv[1]);
//    Service service(config);
//    service.run();
//  } catch (const std::exception &e) {
//    Log::log_with_date_time(std::string("fatal: ") + e.what(), Log::FATAL);
//    Log::log_with_date_time("exiting. . . ", Log::FATAL);
////    exit(1);
//  }
}

App::~App()
{

}
