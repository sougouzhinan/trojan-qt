#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QString>
#include <QByteArray>

namespace Ui {
    class ConfigDialog;
}

class ConfigDialog : public QDialog {
    Q_OBJECT
public:
    explicit ConfigDialog(QWidget *parent = 0);
    void setDefaultConfig();
    ~ConfigDialog();
private:
    Ui::ConfigDialog *ui;
    const static QByteArray defaultConfig;
private slots:
    void certificatePathButtonClicked();
    void accept();
};

#endif // CONFIGDIALOG_H
