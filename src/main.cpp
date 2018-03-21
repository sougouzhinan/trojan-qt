#include "App.h"
#include <QApplication>

#ifdef Q_OS_MAC
#include <QMessageBox>
#include <Authorization.h>
#include <mach-o/dyld.h>
#endif

using namespace std;

#ifdef Q_OS_MAC
bool relaunch_as_root()
{
    QMessageBox msgBox;
    char appPath[2048];
    uint32_t size = sizeof(appPath);
    AuthorizationRef authRef;
    OSStatus status;

    /* Get the path of the current program */
    if (_NSGetExecutablePath(appPath, &size) != 0) {
        msgBox.setText("Could not get program path to elevate privileges.");
        return false;
    }

    status = AuthorizationCreate(NULL, kAuthorizationEmptyEnvironment,
        kAuthorizationFlagDefaults, &authRef);

    if (status != errAuthorizationSuccess) {
        msgBox.setText("Failed to create authorization reference.");
        return false;
    }
    status = AuthorizationExecuteWithPrivileges(authRef, appPath,
        kAuthorizationFlagDefaults, NULL, NULL);
    AuthorizationFree(authRef, kAuthorizationFlagDestroyRights);

    if (status == errAuthorizationSuccess) {
        /* We've successfully re-launched with root privs. */
        return true;
    }

    return false;
}
#endif

int main(int argc, char *argv[]) {
  QCoreApplication::setSetuidAllowed(true);
  App app(argc, argv);

#ifdef Q_OS_MAC
  if (geteuid() != 0) {
      if (relaunch_as_root()) {
          /* We have re-launched with root privs. Exit this process. */
          return 0;
      }

      QMessageBox msgBox;
      msgBox.setText("This program requires root privileges to fully function.");
      msgBox.setInformativeText("Trojan will not be able to read and write key file.");
      msgBox.exec();
      return -1;
  }
#endif

  app.window->show();
  return app.exec();
}

