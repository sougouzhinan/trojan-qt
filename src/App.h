#ifndef APP_H
#define APP_H

#include <QWidget>

class App : public QWidget
{
  Q_OBJECT

public:
  App(QWidget *parent = 0);
  ~App();
};

#endif // APP_H
