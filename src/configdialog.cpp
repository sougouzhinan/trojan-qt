#include "configdialog.h"
#include "ui_configdialog.h"
#include <QFileDialog>

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog) {
    ui->setupUi(this);
    connect(ui->certificatePathButton, SIGNAL(clicked(bool)), this, SLOT(certificatePathButtonClicked()));
}

ConfigDialog::~ConfigDialog() {
    delete ui;
}

void ConfigDialog::setDefaultConfig() {
    ui->name->setText("Server");
    ui->remoteAddress->setText("example.com");
    ui->remotePort->setText("443");
    ui->localPort->setText("1080");
    ui->password->setText("");
    ui->verifyHostname->setChecked(true);
    ui->certificatePath->setText("");
    ui->sni->setText("example.com");
    ui->name->setFocus();
}

void ConfigDialog::certificatePathButtonClicked() {
    QString path = QFileDialog::getOpenFileName(this, "Open Certificate", "", tr("Certificates (*.crt *.pem)"));
    if (path.size() != 0) {
        ui->certificatePath->setText(path.replace('\\', '/'));
    }
}
