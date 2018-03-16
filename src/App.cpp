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
{

#ifdef Q_OS_OSX
  QApplication::setQuitOnLastWindowClosed(false);
#endif

  checkDir(APP_DATA_DIR);




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
          return false;
        }
    }
  return true;
}
