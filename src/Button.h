#ifndef BUTTON_H
#define BUTTON_H

#include <QResizeEvent>
#include <QMouseEvent>
#include <QStaticText>
#include <QFontMetrics>
#include <QPainter>
#include <QPaintEngine>
#include <QOpenGLWidget>

#include <QDebug>

class Button : public QWidget
{
  Q_OBJECT

public:
  enum Palette{
    FgDefault = 0,
    FgHovered = 1,
    BgDefault = 2,
    BgHovered = 3
  };

  explicit Button(const QString &txt, const int &w = 0, const int &h = 100, QWidget *parent = 0);
  explicit Button(const QString &txt, QWidget *parent = 0);

  void setFont(const QFont &f);
  void setFont(const QString &family, const int &pixelSize);
  void setText(const QString &str);

  void setPalette(const Palette &palette, const QColor &color);

protected:
  void paintEvent(QPaintEvent *);
  void resizeEvent(QResizeEvent *ev);
  void mousePressEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);
  void enterEvent(QEvent *ev);
  void leaveEvent(QEvent *ev);

private:
  bool hovered = false;

  int width;
  int height = 30;

  QRect bkg_rect;

  QString text;
  QFont font;

  QColor bg_default_color = QColor(235,250,235);
  QColor bg_hovered_color = QColor(100,200,90);
  QColor fg_default_color = QColor(100,200,90);
  QColor fg_hovered_color = QColor(255,255,255);

  void updateTextRect();

signals:
  void clicked();
};
#endif // BUTTON_H
