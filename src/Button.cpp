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

#include "Button.h"

Button::Button(const QString &str,const int &w, const int &h, QWidget *parent)
  : QWidget(parent)
  , width(w)
  , height(h)
  , text(str)
{
  setText(str);
  setFont("Gill Sans Light", 13);
  this->setAutoFillBackground(true);
  this->setFixedSize(QSize(w,h));
}

Button::Button(const QString &str, QWidget *parent)
  : QWidget(parent)
  , height(30)
{
  setText(str);
  setFont("Gill Sans Light", 13);
  this->setAutoFillBackground(true);
  this->setMinimumSize(QSize(width, height));
}

void Button::setFont(const QFont &f)
{
  font = f;
  updateText();
}

void Button::setFont(const QString &family, const int &pixelSize)
{
  font.setFamily(family);
  font.setPixelSize(14);
  updateText();
}

void Button::setText(const QString &str)
{
  text = str;
  updateText();
}

void Button::setColorOption(const Button::ColorOption &palette, const QColor &color)
{
  switch (palette) {
    case ColorOption::BgDefault:
      {
        bg_default_color = color;
        break;
      }
    case ColorOption::BgHovered:
      {
        bg_hovered_color = color;
        break;
      }
    case ColorOption::FgDefault:
      {
        fg_default_color = color;
        break;
      }
    case ColorOption::FgHovered:
      {
        fg_hovered_color = color;
        break;
      }
    default:
      break;
    }
}

void Button::paintEvent(QPaintEvent *)
{
  QPainter p;
  p.begin(this);
  p.setRenderHint(QPainter::Antialiasing,true);
  p.setPen(Qt::NoPen);
  p.setBrush(QBrush(hovered ? bg_hovered_color :bg_default_color, Qt::SolidPattern));
  p.drawRoundedRect(bg_rect,8,8);

  QTextOption textOption;
  textOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
  textOption.setAlignment(Qt::AlignCenter);
  p.setPen(hovered ? fg_hovered_color : fg_default_color);
  p.setFont(font);
  p.drawText(this->rect(), text, textOption);
  p.end();
}

void Button::resizeEvent(QResizeEvent *ev)
{
  bg_rect = QRect(1, (this->rect().height() - height) * 0.5 + 1, this->rect().width() - 1, height - 1);
  QWidget::resizeEvent(ev);
}

void Button::mousePressEvent(QMouseEvent *)
{

}

void Button::mouseReleaseEvent(QMouseEvent *)
{
  emit clicked();
}

void Button::enterEvent(QEvent *)
{
  hovered = true;
  this->update();
}

void Button::leaveEvent(QEvent *)
{
  hovered = false;
  this->update();
}

void Button::updateText()
{
  QFontMetrics metrics(font);
  width = metrics.width(text) + 40;
  update();
}




