#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCoreApplication>

#include "version.h"

class Window : public QWidget
{
  Q_OBJECT
public:
  explicit Window(QWidget *parent = nullptr);

signals:

public slots:

private:
  QMenu *tray_menu;
  QAction *hide_action;
  QAction *show_action;
  QAction *quit_action;
  QSystemTrayIcon *tray_icon;
};

#endif // WINDOW_H
