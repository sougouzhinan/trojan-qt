#ifndef GUITEXTBUTTON_H
#define GUITEXTBUTTON_H

#include <QLabel>
#include <QMouseEvent>

class TextButton : public QLabel
{
  Q_OBJECT

public:
  explicit TextButton(QWidget *parent = 0);
  TextButton(const QString &text);

  void setFontPixelSize(int size);
  void setDefaultTextColor(const QColor &color);
  void setHoveredTextColor(const QColor &color);

signals:
  void clicked();
  void entered();
  void left();

protected:
    void mouseReleaseEvent(QMouseEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

private:
     QPalette palette;
     int font_pixel_size = 18;
     QColor text_color = QColor(106,74,0,255);
     QColor hovered_text_color = QColor(255,188,0,255);

};

#endif // GUITEXTBUTTON_H
