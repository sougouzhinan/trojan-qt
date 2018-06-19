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
  , stacked_widget(new QStackedWidget(this))
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

  ConfigEditor *e = new ConfigEditor(this);
  stacked_widget->addWidget(e);
  stacked_widget->setContentsMargins(0,0,0,0);
  scroll_area = new QScrollArea(this);
  scroll_area->setWidgetResizable(true);
  scroll_area->setWidget(stacked_widget);
  scroll_area->setMinimumWidth(450);
  scroll_area->setHidden(true);
  scroll_area->setFrameStyle(0);
  scroll_area->setContentsMargins(0,0,0,0);

  QPalette p(this->palette());
  p.setColor(QPalette::Foreground, QColor(120,120,120));
  p.setColor(QPalette::Window, QColor(250,0,250));
  scroll_area->setPalette(p);

  main_layout->setSpacing(0);
  main_layout->setMargin(0);
  main_layout->addWidget(body_widget);
  main_layout->addWidget(scroll_area);
  main_layout->setSizeConstraint(QLayout::SetFixedSize);

  connect(hide_action, &QAction::triggered, this, &QWidget::hide);
  connect(show_action, &QAction::triggered, [this](){this->show();this->raise();});
  connect(quit_action, &QAction::triggered, qApp, &QCoreApplication::quit);
  connect(tray_icon, &QSystemTrayIcon::activated, [this](){this->show();this->raise();});
  connect(body_widget->start_button, &Button::clicked, this, &Window::onStartButtonClicked);
  connect(body_widget->server_rbutton, &QRadioButton::toggled, this, &Window::onModeSwitched);
  connect(body_widget->config_button, &Button::clicked, [this](){
          if(isEditing)
            {
              scroll_area->setHidden(true);
              body_widget->config_button->setText("Edit Config");
              body_widget->config_button->setTheme(Button::Gray);
              isEditing = !isEditing;
            }
          else
            {
              scroll_area->setHidden(false);
              body_widget->config_button->setText("Save Config");
              body_widget->config_button->setTheme(Button::Amber);
              isEditing = !isEditing;
            }
    });

  QFont font;
  font.setFamily("Verdana");
  font.setPixelSize(14);
  this->setFont(font);

  QPalette palette(this->palette());
  palette.setColor(QPalette::Window, Qt::white);
  this->setPalette(palette);
  this->setMinimumSize(QSize(250,0));
  this->setWindowTitle(QString("Trojan Qt"));

#ifndef Q_OS_OSX
  this->setWindowIcon(QIcon(":/img/img/logo.png"));
#endif


}

void Window::onServerStarted(const bool &sucess)
{
  if(sucess)
    {
      body_widget->setEnabled(true);
      body_widget->setStartButtonState(BodyWidget::Stop);
    }
  else
    {
      body_widget->setEnabled(true);
      body_widget->setStartButtonState(BodyWidget::Start);
    }
}

void Window::onStartButtonClicked()
{
  body_widget->setEnabled(false);/*
  body_widget->start_button->setEnabled(false);
  body_widget->config_button->setEnabled(false);*/
  body_widget->setStartButtonState(BodyWidget::Disabled);
  emit startTriggered();
}


void Window::onModeSwitched(bool checked)
{
  if(checked)
    {
      emit modeSwiched(Config::SERVER);
      qDebug()<<"server mode";
    }
  else
    {
      emit modeSwiched(Config::CLIENT);
      qDebug()<<"client mode";
    }
}
