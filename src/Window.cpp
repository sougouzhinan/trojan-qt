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

#include "Window.h"

Window::Window(QWidget *parent)
  : QWidget(parent)
  , hide_action(new QAction(tr("&Hide"), this))
  , show_action(new QAction(tr("&Show"), this))
  , quit_action(new QAction(tr("&Quit"), this))
  , tray_menu(new QMenu(this))
  , tray_icon(new QSystemTrayIcon(this))
  , main_layout(new QHBoxLayout(this))
  , body_widget(new BodyWidget(this))
  , stacked_widget(new StackedWidget(this))
{
  tray_menu->addAction(hide_action);
  tray_menu->addAction(show_action);
  tray_menu->addSeparator();
  tray_menu->addAction(quit_action);

  tray_icon->setContextMenu(tray_menu);
  tray_icon->setIcon(QIcon(":/img/img/logo.png"));
  tray_icon->setToolTip("Trojan Qt5");
  tray_icon->setVisible(true);
  tray_icon->show();

  main_layout->setSpacing(0);
  main_layout->setMargin(0);
  main_layout->addWidget(body_widget);
  main_layout->addWidget(stacked_widget);

  connect(hide_action, &QAction::triggered, this, &QWidget::hide);
  connect(show_action, &QAction::triggered, [this](){this->show();this->raise();});
  connect(quit_action, &QAction::triggered, qApp, &QCoreApplication::quit);
  connect(tray_icon, &QSystemTrayIcon::activated, [this](){this->show();this->raise();});

  QPalette palette(this->palette());
  palette.setColor(QPalette::Window, Qt::white);
  this->setPalette(palette);
  this->setMinimumSize(QSize(250,0));
  this->setWindowTitle(QString("Trojan Qt  v%1.%2.%3").arg(VERSION_1).arg(VERSION_2).arg(VERSION_3));
#ifndef Q_OS_OSX
  this->setWindowIcon(QIcon(":/img/img/logo.png"));
#endif


}
