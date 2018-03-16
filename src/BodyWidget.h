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


class BodyWidget : public QWidget
{
  Q_OBJECT
public:
  explicit BodyWidget(QWidget *parent = nullptr);

private:
  QLabel *logo_label;
  QLabel *mode_label;
  QRadioButton *server_rbutton;
  QRadioButton *client_rbutton;
  Button *start_button;
  Button *config_button;
  IconButton *settings_button;
};

#endif // BODYWIDGET_H
