#ifndef SERVICETHREAD_H
#define SERVICETHREAD_H

#include <QThread>
#include "trojan/src/service.h"
#include "trojan/src/config.h"

class ServiceThread : public QThread {
  Q_OBJECT
private:
  Service *service;
  Config *_config;
  void cleanUp();
public:
  ServiceThread(QObject *parent = nullptr);
  Config& config();
  ~ServiceThread();
protected:
  void run();
public slots:
  void stop();
signals:
  void started();
  void exception(const QString &what);
};

#endif // SERVICETHREAD_H
