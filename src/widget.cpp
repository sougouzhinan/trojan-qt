#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    trojan(this) {
    ui->setupUi(this);
}

Widget::~Widget() {
    delete ui;
}
