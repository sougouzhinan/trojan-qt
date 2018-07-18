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

#ifndef PATHUTILS_H
#define PATHUTILS_H

#include <QStringList>
#include <QByteArray>

class PathUtils {
private:
    static QString prefix;
    static QString configPath;
    static QString logPath;
    static void createIfNotExists(const QString &path);
public:
    static void init();
    static void openFolder();
    static QStringList listConfig();
    static QString configFullPath(const QString &config);
    static bool configExists(const QString &config);
    static bool addConfig(const QString &name, const QByteArray &content);
    static bool deleteConfig(const QString &config);
    static void redirectStderr();
};

#endif // PATHUTILS_H
