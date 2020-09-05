#ifndef NTPCLIENT_H
#define NTPCLIENT_H
#include <QObject>
#include "networklayer.h"
#include <QTimer>

class NtpClient : public QObject
{
    Q_OBJECT
    NetWorkLayer *m_netWorkLayer;
    QTimer timer;
public:
    NtpClient(const unsigned short _port);
    bool createSocket();
    void buildClientInfo();
    void changePcTime(QDateTime &datetime);
    void startNtp();
public slots:
    void getRemoteTime();
};

#endif // NTPCLIENT_H
