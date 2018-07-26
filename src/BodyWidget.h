#ifndef BODYWIDGET_H
#define BODYWIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCoreApplication>
#include <Button.h>
#include <QVBoxLayout>
#include <QLabel>
#include <QRadioButton>

#include "Version.h"
#include "IconButton.h"
#include "AppManager.h"


class BodyWidget : public QWidget
{
  Q_OBJECT
public:
  enum StartButtonState {
    Disabled = 1,
    Start = 2,
    Stop = 3
  };

  explicit BodyWidget(QWidget *parent = nullptr);
  Button *start_button;
  Button *config_button;
  IconButton *settings_button;
  QRadioButton *server_rbutton;
  QRadioButton *client_rbutton;

public slots:
  void setStartButtonState(StartButtonState state);


private:
  QLabel *logo_label;
  QLabel *mode_label;
};

#endif // BODYWIDGET_H
