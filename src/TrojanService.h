#ifndef TROJANSERVICE_H
#define TROJANSERVICE_H

#include <QObject>
#include "ServiceThread.h"

class TrojanService : public QObject {
  Q_OBJECT
private:
  ServiceThread *thread;
  Config *_config;
public:
  TrojanService(QObject *parent = nullptr);
  Config& config();
  bool started();
  ~TrojanService();
public slots:
  void start();
  void stop();
};

#endif // TROJANSERVICE_H
