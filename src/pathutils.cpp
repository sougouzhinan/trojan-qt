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

#include "pathutils.h"
#include <QStandardPaths>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>
#include <QFile>
#include <QDateTime>
#include <QTextStream>

QString PathUtils::prefix;
QString PathUtils::configPath;
QString PathUtils::logPath;

void PathUtils::createIfNotExists(const QString &path) {
    if (!QDir(path).exists()) {
        QDir().mkpath(path);
    }
}

void PathUtils::init() {
    prefix = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + '/';
    configPath = prefix + "config/";
    logPath = prefix + "log/";
    createIfNotExists(configPath);
    createIfNotExists(logPath);
}

void PathUtils::openFolder() {
    QDesktopServices::openUrl(QUrl::fromLocalFile(prefix));
}

QStringList PathUtils::listConfig() {
    QDir dir(configPath);
    dir.setNameFilters(QStringList("*.json"));
    dir.setFilter(QDir::Files | QDir::Readable);
    dir.setSorting(QDir::Name);
    QStringList ret(dir.entryList());
    ret.replaceInStrings(QRegExp(".json$"), "");
    return ret;
}

QString PathUtils::configFullPath(const QString &config) {
    return configPath + config + ".json";
}

bool PathUtils::configExists(const QString &config) {
    return QFile(configFullPath(config)).exists();
}

bool PathUtils::addConfig(const QString &name, const QByteArray &content) {
    QFile file(configFullPath(name));
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << content;
        file.close();
        return true;
    }
    return false;
}

bool PathUtils::deleteConfig(const QString &config) {
    return QFile(configFullPath(config)).remove();
}

void PathUtils::redirectStderr() {
    QString time(QDateTime::currentDateTime().toString("yyyyMMddHHmmss"));
    freopen((logPath + "trojan_" + time + ".log").toLocal8Bit().data(), "a", stderr);
}
