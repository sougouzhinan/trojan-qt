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

#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include "pathutils.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    trojan(this),
    configDialog(this),
    configListModel(this) {
    ui->setupUi(this);
    ui->configList->setModel(&configListModel);
    refreshConfigList();
    connect(ui->addButton, SIGNAL(clicked(bool)), this, SLOT(addButtonClicked()));
    connect(ui->deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteButtonClicked()));
    connect(ui->refreshButton, SIGNAL(clicked(bool)), this, SLOT(refreshButtonClicked()));
    connect(ui->openFolderButton, SIGNAL(clicked(bool)), this, SLOT(openFolderButtonClicked()));
    connect(ui->startButton, SIGNAL(clicked(bool)), this, SLOT(startButtonClicked()));
    connect(&trojan, SIGNAL(trojanStarted()), this, SLOT(trojanStarted()));
    connect(&trojan, SIGNAL(trojanFailed(QString)), this, SLOT(trojanFailed(QString)));
    connect(&configDialog, SIGNAL(accepted()), this, SLOT(refreshButtonClicked()));
}

Widget::~Widget() {
    delete ui;
}

void Widget::refreshConfigList() {
    configListModel.setStringList(PathUtils::listConfig());
}

QString Widget::selectedConfig() {
    QModelIndexList list(ui->configList->selectionModel()->selectedIndexes());
    if (list.size() == 0) {
        QMessageBox::critical(this, "Critical", "Select a config!");
        return "";
    }
    return list.first().data().toString();
}

void Widget::addButtonClicked() {
    configDialog.setDefaultConfig();
    configDialog.show();
}

void Widget::deleteButtonClicked() {
    QString selected(selectedConfig());
    if (selected == "") {
        return;
    }
    if (!PathUtils::deleteConfig(selected)) {
        QMessageBox::critical(this, "Critical", "Delete failed!");
    }
    refreshConfigList();
}

void Widget::refreshButtonClicked() {
    refreshConfigList();
}

void Widget::openFolderButtonClicked() {
    PathUtils::openFolder();
}

void Widget::startButtonClicked() {
    if (trojan.isRunning()) {
        trojan.stopTrojan();
        ui->startButton->setText("Start");
        ui->startButton->repaint();
    } else {
        QString selected(selectedConfig());
        if (selected == "") {
            return;
        }
        PathUtils::redirectStderr();
        trojan.startTrojan(PathUtils::configFullPath(selected));
        ui->startButton->setText("Starting");
        ui->startButton->setEnabled(false);
    }
}

void Widget::trojanStarted() {
    ui->startButton->setText("Stop");
    ui->startButton->setEnabled(true);
}

void Widget::trojanFailed(QString errorMessage) {
    QMessageBox::critical(this, "Critical", errorMessage);
    ui->startButton->setText("Start");
    ui->startButton->setEnabled(true);
}
