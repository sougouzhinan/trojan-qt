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
