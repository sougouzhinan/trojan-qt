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

#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCoreApplication>
#include <Button.h>
#include <QVBoxLayout>
#include <QLabel>

#include "Version.h"
#include "BodyWidget.h"
#include "StackedWidget.h"

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

  QHBoxLayout *main_layout;
  BodyWidget *body_widget;
  StackedWidget *stacked_widget;

  bool isEditing = false;
};

#endif // WINDOW_H
