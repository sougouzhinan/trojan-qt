#include "Window.h"

Window::Window(QWidget *parent)
  : QWidget(parent)
  , hide_action(new QAction(tr("&Hide"), this))
  , show_action(new QAction(tr("&Show"), this))
  , quit_action(new QAction(tr("&Quit"), this))
  , tray_menu(new QMenu(this))
  , tray_icon(new QSystemTrayIcon(this))
  , logo_label(new QLabel(this))
  , start_button(new Button("Start", this))
  , config_button(new Button("Edit Config...", this))
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

  QPixmap pixmap(":/img/img/logo.png");
  pixmap.setDevicePixelRatio(2.0);
  logo_label->setPixmap(pixmap.scaledToWidth(300, Qt::SmoothTransformation));
  logo_label->setAlignment(Qt::AlignCenter);

  config_button->setPalette(Button::FgDefault, QColor(150,150,150));
  config_button->setPalette(Button::FgHovered, QColor(100,100,100));
  config_button->setPalette(Button::BgDefault, QColor(255,255,255));
  config_button->setPalette(Button::BgHovered, QColor(240,240,240));

  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  mainLayout->setSpacing(0);
  mainLayout->addSpacing(20);
  mainLayout->addWidget(logo_label);
  mainLayout->addSpacing(50);
  mainLayout->addWidget(start_button);
  mainLayout->addSpacing(8);
  mainLayout->addWidget(config_button);

  connect(hide_action, &QAction::triggered, this, &QWidget::hide);
  connect(show_action, &QAction::triggered, [this](){this->show();this->raise();});
  connect(quit_action, &QAction::triggered, qApp, &QCoreApplication::quit);
  connect(tray_icon, &QSystemTrayIcon::activated, [this](){this->show();this->raise();});

  QPalette palette(this->palette());
  palette.setColor(QPalette::Window, Qt::white);
  this->setPalette(palette);
  this->setMinimumSize(QSize(250,0));
  this->setWindowTitle(QString("Trojan-Qt  v%1.%2.%3").arg(VERSION_1).arg(VERSION_2).arg(VERSION_3));
#ifndef Q_OS_OSX
  this->setWindowIcon(QIcon(":/img/img/logo.png"));
#endif


}
