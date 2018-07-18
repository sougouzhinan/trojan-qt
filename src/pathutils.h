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
