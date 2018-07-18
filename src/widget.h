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
