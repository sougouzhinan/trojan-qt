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
