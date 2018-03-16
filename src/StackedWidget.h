#ifndef STACKEDWIDGET_H
#define STACKEDWIDGET_H

#include <QWidget>
#include <QStackedWidget>


class StackedWidget : public QWidget
{
  Q_OBJECT
public:
  explicit StackedWidget(QWidget *parent = nullptr);

  QStackedWidget *stacked_widget;


signals:

public slots:
};

#endif // STACKEDWIDGET_H
