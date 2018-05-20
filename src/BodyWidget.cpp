#include "BodyWidget.h"

BodyWidget::BodyWidget(QWidget *parent)
  : QWidget(parent)
  , logo_label(new QLabel(this))
  , mode_label(new QLabel("Mode:  ", this))
  , server_rbutton(new QRadioButton("Server", this))
  , client_rbutton(new QRadioButton("Client", this))
  , start_button(new Button("Start", this))
  , config_button(new Button("Edit Config", this))
  , settings_button(new IconButton(this))
{
  QPixmap logoPixmap(":/img/img/logo.png");
  logoPixmap.setDevicePixelRatio(2.0);
  logo_label->setPixmap(logoPixmap.scaledToWidth(300, Qt::SmoothTransformation));
  logo_label->setAlignment(Qt::AlignCenter);

  mode_label->setStyleSheet("QLabel{color:#999999}");

  server_rbutton->setStyleSheet("QRadioButton{color:#999999}");

  client_rbutton->setStyleSheet("QRadioButton{color:#999999}");
  client_rbutton->setChecked(true);

  QHBoxLayout *mode_layout = new QHBoxLayout();
  mode_layout->setAlignment(Qt::AlignCenter);
  mode_layout->addWidget(mode_label);
  mode_layout->addWidget(server_rbutton);
  mode_layout->addWidget(client_rbutton);

  config_button->setTheme(Button::Gray);

  settings_button->setDefaultPixmap(":/img/img/settings_default.png", 50);
  settings_button->setHoveredPixmap(":/img/img/settings_hovered.png", 50);
  settings_button->setPressedPixmap(":/img/img/settings_hovered.png", 50);
  settings_button->setAlignment(Qt::AlignCenter);

  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  mainLayout->setContentsMargins(30,0,30,20);
  mainLayout->setSpacing(0);
  mainLayout->addSpacing(20);
  mainLayout->addWidget(logo_label);
  mainLayout->addSpacing(20);
  mainLayout->addWidget(start_button);
  mainLayout->addSpacing(8);
  mainLayout->addWidget(config_button);
  mainLayout->addSpacing(8);
  mainLayout->addLayout(mode_layout);
  mainLayout->addSpacing(80);
  mainLayout->addWidget(settings_button);

  QPalette palette(this->palette());
//  palette.setColor(QPalette::Window, QColor(255,255,250));
  palette.setColor(QPalette::Window, QColor(255,255,255));
  this->setAutoFillBackground(true);
  this->setPalette(palette);
  this->setFixedWidth(250);
  setStartButtonState(StartButtonState::Start);
}

void BodyWidget::setStartButtonState(BodyWidget::StartButtonState state)
{
  switch (state) {
    case StartButtonState::Disabled:
      start_button->setTheme(Button::Gray);
      start_button->setText("Starting");
      break;
    case StartButtonState::Start:
      start_button->setTheme(Button::Green);
      start_button->setText("Start");
      break;
    case StartButtonState::Stop:
      start_button->setTheme(Button::Amber);
      start_button->setText("Stop");
      break;
    default:
      break;
    }
}

