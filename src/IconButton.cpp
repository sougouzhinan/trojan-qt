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

#include "IconButton.h"

IconButton::IconButton(QWidget *parent)
  : QLabel(parent)
{
}

void IconButton::setDefaultPixmap(const QString &path)
{
  default_pixmap.load(path);
  default_pixmap.setDevicePixelRatio(2.0);
  this->setPixmap(default_pixmap);
}

void IconButton::setHoveredPixmap(const QString &path)
{
  hovered_pixmap.load(path);
  hovered_pixmap.setDevicePixelRatio(2.0);
}

void IconButton::setPressedPixmap(const QString &path)
{
  pressed_pixmap.load(path);
  pressed_pixmap.setDevicePixelRatio(2.0);
}

void IconButton::setDefault()
{
      this->setPixmap(default_pixmap);
}

void IconButton::setHovered()
{
      this->setPixmap(hovered_pixmap);
}

void IconButton::enterEvent(QEvent *)
{
  setHovered();
  emit entered();
}

void IconButton::leaveEvent(QEvent *)
{
  setDefault();
  emit left();
}

void IconButton::mousePressEvent(QMouseEvent *ev)
{
  if (ev->button() == Qt::LeftButton)
      if(!pressed_pixmap.isNull())
          this->setPixmap(pressed_pixmap);
}

void IconButton::mouseReleaseEvent(QMouseEvent *ev)
{
  if (ev->button() == Qt::LeftButton)
      emit clicked();
}


