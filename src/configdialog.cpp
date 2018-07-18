/*
 * This file is part of the trojan-gui project.
 * Trojan is an unidentifiable mechanism that helps you bypass GFW.
 * Copyright (C) 2018  GreaterFire
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

#include "configdialog.h"
#include "ui_configdialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QLineEdit>
#include <QCheckBox>
#include "pathutils.h"

const QByteArray ConfigDialog::defaultConfig(
    "{"
    "    \"run_type\": \"client\","
    "    \"local_addr\": \"127.0.0.1\","
    "    \"local_port\": 1080,"
    "    \"remote_addr\": \"example.com\","
    "    \"remote_port\": 443,"
    "    \"password\": [\"password1\"],"
    "    \"append_payload\": true,"
    "    \"log_level\": 1,"
    "    \"ssl\": {"
    "        \"verify\": true,"
    "        \"verify_hostname\": true,"
    "        \"cert\": \"\","
    "        \"cipher\": \"ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-CHACHA20-POLY1305:ECDHE-RSA-CHACHA20-POLY1305:ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384:ECDHE-ECDSA-AES256-SHA:ECDHE-ECDSA-AES128-SHA:ECDHE-RSA-AES128-SHA:ECDHE-RSA-AES256-SHA:DHE-RSA-AES128-SHA:DHE-RSA-AES256-SHA:AES128-SHA:AES256-SHA:DES-CBC3-SHA\","
    "        \"sni\": \"example.com\","
    "        \"alpn\": ["
    "            \"h2\","
    "            \"http/1.1\""
    "        ],"
    "        \"reuse_session\": true,"
    "        \"curves\": \"\","
    "        \"sigalgs\": \"\""
    "    },"
    "    \"tcp\": {"
    "        \"keep_alive\": true,"
    "        \"no_delay\": true,"
    "        \"fast_open\": true,"
    "        \"fast_open_qlen\": 5"
    "    }"
    "}"
);

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
    QJsonObject config(QJsonDocument::fromJson(defaultConfig).object());
    config.find("remote_addr").value() = ui->remoteAddress->text();
    config.find("remote_port").value() = remotePort;
    config.find("local_port").value() = localPort;
    QJsonArray password;
    password.append(ui->password->text());
    config.find("password").value() = password;
    QJsonObject ssl = config.find("ssl").value().toObject();
    ssl.find("verify_hostname").value() = ui->verifyHostname->isChecked();
    ssl.find("cert").value() = ui->certificatePath->text();
    ssl.find("sni").value() = ui->sni->text();
    config.find("ssl").value() = ssl;
    if (PathUtils::addConfig(ui->name->text(), QJsonDocument(config).toJson())) {
        emit accepted();
        hide();
    } else {
        QMessageBox::critical(this, "Critical", "Add failed!");
    }
}
