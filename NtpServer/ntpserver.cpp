#include "ntpserver.h"
#include <QDebug>
NtpServer::NtpServer(unsigned short _port)
{
    this->m_networklayer = new NetWorkLayer(_port);
}

bool NtpServer::createSocket()
{
    bool l_flag = this->m_networklayer->createSocket();
    if(l_flag)
        this->m_networklayer->setSocketOpt();
    return l_flag;
}

bool NtpServer::bindServer()
{
    return this->m_networklayer->bindServer();
}

void NtpServer::buildServerInfo()
{
    this->m_networklayer->buildServerInfo();
}

void NtpServer::listen()
{
    qDebug()  << "listen";
    while (true) {
        QString l_request;
        if((this->m_networklayer->readFrom(l_request)) && (l_request.compare("getDate") == 0)){
            QDateTime datetime = QDateTime::currentDateTime();
            this->m_networklayer->sendTo(datetime);
            qDebug() << "Clien ip:" << this->m_networklayer->getClientIp() << " Client hostname:" << this->m_networklayer->getClientHostName() << " request:" << l_request;
        }

    }
}
