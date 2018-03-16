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

#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QDebug>

#include <QMouseEvent>
#include <QLabel>

class IconButton : public QLabel
{
  Q_OBJECT

public:
  explicit IconButton(QWidget *parent = 0);

  void setDefaultPixmap(const QString &path, const int &height);
  void setHoveredPixmap(const QString &path, const int &height);
  void setPressedPixmap(const QString &path, const int &height);
  void setDefault();
  void setHovered();

signals:
  void clicked();
  void entered();
  void left();

protected:
  void enterEvent(QEvent *);
  void leaveEvent(QEvent *);
  void mousePressEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);

private:
  QPixmap default_pixmap;
  QPixmap hovered_pixmap;
  QPixmap pressed_pixmap;
};

#endif // ICONBUTTON_H
