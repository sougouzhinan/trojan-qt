#ifndef SERVICETHREAD_H
#define SERVICETHREAD_H

#include <QThread>
#include "trojan/src/service.h"
#include "trojan/src/config.h"

class ServiceThread : public QThread {
  Q_OBJECT
public:
  ServiceThread(Config &config, QObject *parent = nullptr);
  void stop();
  ~ServiceThread();
private:
  Service *service;
protected:
  void run();
};

#endif // SERVICETHREAD_H
