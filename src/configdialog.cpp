#include "configdialog.h"
#include "ui_configdialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include "pathutils.h"

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

void ConfigDialog::accept() {
    if (PathUtils::configExists(ui->name->text())) {
        QMessageBox::critical(this, "Critical", "Name exists!");
        return;
    }
    bool ok;
    uint16_t remotePort = ui->remotePort->text().toUInt(&ok);
    if (!ok) {
        QMessageBox::critical(this, "Critical", "Remote port has to be a positive integer!");
        ui->remotePort->setFocus();
        return;
    }
    uint16_t localPort = ui->localPort->text().toUInt(&ok);
    if (!ok) {
        QMessageBox::critical(this, "Critical", "Local port has to be a positive integer!");
        ui->localPort->setFocus();
        return;
    }
    if (PathUtils::addConfig(ui->name->text(), "")) {
        emit accepted();
        hide();
    } else {
        QMessageBox::critical(this, "Critical", "Add failed!");
    }
}
