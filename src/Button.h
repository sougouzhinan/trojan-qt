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
  enum ColorOption{
    FgDefault = 0,
    FgHovered = 1,
    BgDefault = 2,
    BgHovered = 3
  };

  enum Theme{
    Green = 0,
    Amber = 1,
    Gray = 3
  };

  explicit Button(const QString &str, const int &w = 0, const int &h = 100, QWidget *parent = 0);
  explicit Button(const QString &str, QWidget *parent = 0);

  void setFont(const QFont &f);
  void setFont(const QString &family, const int &pixelSize);
  void setText(const QString &str);

  void setColor(const ColorOption &palette, const QColor &color);
  void setTheme(const Theme &theme);

protected:
  void paintEvent(QPaintEvent *);
  void resizeEvent(QResizeEvent *ev);
  void mousePressEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);
  void enterEvent(QEvent *);
  void leaveEvent(QEvent *);

private:
  bool hovered = false;

  int width;
  int height;

  QRect bg_rect;
  QFont font;
  QString text;

  QColor bg_default_color = QColor(230,245,225);
  QColor bg_hovered_color = QColor(100,200,90);
  QColor fg_default_color = QColor(100,200,90);
  QColor fg_hovered_color = QColor(255,255,255);

  void updateText();

signals:
  void clicked();
};
#endif // BUTTON_H
