#include "Button.h"

Button::Button(const QString &txt,const int &w, const int &h, QWidget *parent)
  : QWidget(parent)
  , width(w)
  , height(h)
  , text(txt)
{
  setFont("Gill Sans Light", 14);
  setText(txt);
  this->setFixedSize(QSize(w,h));
  this->setAutoFillBackground(true);
}

Button::Button(const QString &txt, QWidget *parent)
  : QWidget(parent)
{
  setFont("Gill Sans Light", 13);
  setText(txt);
  this->setMinimumSize(QSize(width, height));
  this->setAutoFillBackground(true);
}

void Button::setFont(const QFont &f)
{
  font = f;
  updateTextRect();

}

void Button::setFont(const QString &family, const int &pixelSize)
{
  font.setFamily(family);
  font.setPixelSize(14);
  updateTextRect();
}

void Button::setText(const QString &str)
{
  text = str;
  updateTextRect();
}

void Button::setPalette(const Button::Palette &palette, const QColor &color)
{
  switch (palette) {
    case Palette::BgDefault:
      {
        bg_default_color = color;
        break;
      }
    case Palette::BgHovered:
      {
        bg_hovered_color = color;
        break;
      }
      break;
    case Palette::FgDefault:
      {
        fg_default_color = color;
        break;
      }
      break;
    case Palette::FgHovered:
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
  p.setPen(Qt::NoPen);
  p.setBrush(QBrush(hovered ? bg_hovered_color :bg_default_color, Qt::SolidPattern));
  p.setRenderHint(QPainter::Antialiasing,true);
  p.drawRoundedRect(bkg_rect,5,5);
  QTextOption textOption;
  textOption.setAlignment(Qt::AlignCenter);
  textOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
  p.setFont(font);
  p.setPen(hovered ? fg_hovered_color : fg_default_color);
  p.drawText(this->rect(), text, textOption);
//  if (painter.paintEngine()->type() != QPaintEngine::OpenGL2) {
//          qWarning("OpenGLScene: drawBackground needs a QGLWidget to be set as viewport on the graphics view");
//          qDebug()<<painter.paintEngine()->type();
//          return;
//      }
  p.end();
}

void Button::resizeEvent(QResizeEvent *ev)
{
  bkg_rect = QRect(1, (this->rect().height() - height) * 0.5 + 1, this->rect().width() - 1, height - 1);
  QWidget::resizeEvent(ev);
}

void Button::mousePressEvent(QMouseEvent *)
{

}

void Button::mouseReleaseEvent(QMouseEvent *)
{
  emit clicked();
}

void Button::enterEvent(QEvent *ev)
{
  hovered = true;
  this->update();
}

void Button::leaveEvent(QEvent *ev)
{
  hovered = false;
  this->update();
}

void Button::updateTextRect()
{
  QFontMetrics metrics(font);
  width = metrics.width(text) + 40;
  update();
}




