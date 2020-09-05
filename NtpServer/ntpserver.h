#ifndef NTPSERVER_H
#define NTPSERVER_H

#include "networklayer.h"

class NtpServer
{
    NetWorkLayer *m_networklayer;
public:
    NtpServer(unsigned short _port);
    bool createSocket();
    bool bindServer();
    void buildServerInfo();
    void listen();
};

#endif // NTPSERVER_H
