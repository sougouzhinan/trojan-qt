#include "TextButton.h"

TextButton::TextButton(QWidget *parent)
{
  palette.setColor(QPalette::WindowText, text_color);
  this->setPalette(palette);

  this->setParent(parent);

}

TextButton::TextButton(const QString &text)
{
  palette.setColor(QPalette::WindowText, text_color);
  this->setPalette(palette);

  QFont font;
  font.setPointSize(font_pixel_size);
  this->setFont(font);

  this->setText(text);
}

void TextButton::setFontPixelSize(int size)
{
  font_pixel_size = size;
  QFont font;
  font.setPointSize(font_pixel_size);
  this->setFont(font);
}

void TextButton::setDefaultTextColor(const QColor &color)
{
  text_color = color;
  this->setPalette(palette);
}

void TextButton::setHoveredTextColor(const QColor &color)
{
  hovered_text_color = color;
  this->setPalette(palette);
}

////////////events

void TextButton::mouseReleaseEvent(QMouseEvent *ev)
{
  if (ev->button() == Qt::LeftButton)
  emit clicked();
}

void TextButton::enterEvent(QEvent * )
{
  palette.setColor(QPalette::WindowText,hovered_text_color);
  this->setPalette(palette);

  emit entered();
}

void TextButton::leaveEvent(QEvent *)
{
  palette.setColor(QPalette::WindowText, text_color);
  this->setPalette(palette);

  emit left();
}

