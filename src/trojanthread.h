#ifndef TROJANTHREAD_H
#define TROJANTHREAD_H

#include <QThread>
#include <QString>
#include "trojan/src/service.h"

class TrojanThread : public QThread {
    Q_OBJECT
private:
    Service *service;
    QString configPath;
    void cleanup();
public:
    explicit TrojanThread(QObject *parent = 0);
    void startTrojan(const QString &configPath);
    void stopTrojan();
    ~TrojanThread();
protected:
    void run();
signals:
    void trojanStarted();
    void trojanFailed(QString errorMessage);
};

#endif // TROJANTHREAD_H
