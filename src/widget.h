#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStringListModel>
#include "trojanthread.h"
#include "configdialog.h"

namespace Ui {
    class Widget;
}

class Widget : public QWidget {
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
private:
    Ui::Widget *ui;
    TrojanThread trojan;
    ConfigDialog configDialog;
    QStringListModel configListModel;
    void refreshConfigList();
    QString selectedConfig();
private slots:
    void addButtonClicked();
    void deleteButtonClicked();
    void refreshButtonClicked();
    void openFolderButtonClicked();
    void startButtonClicked();
    void trojanStarted();
    void trojanFailed(QString errorMessage);
};

#endif // WIDGET_H
