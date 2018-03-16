#include "StackedWidget.h"

StackedWidget::StackedWidget(QWidget *parent)
  : QWidget(parent)
  , stacked_widget(new QStackedWidget(this))
{


  QPalette palette(this->palette());
  palette.setColor(QPalette::Window, Qt::white);
  this->setPalette(palette);
  this->setAutoFillBackground(true);
  this->setMinimumSize(QSize(350,0));
}
