#include "widget.h"
#include <QApplication>
#include "pathutils.h"

int main(int argc, char *argv[]) {
    QApplication::setApplicationName("trojan-gui");
    QApplication a(argc, argv);
    PathUtils::init();
    Widget w;
    w.show();
    return a.exec();
}
