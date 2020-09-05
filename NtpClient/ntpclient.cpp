#include "ntpclient.h"
#include <QDebug>
NtpClient::NtpClient(const unsigned short _port)
{
    m_netWorkLayer = new NetWorkLayer(_port);
}

bool NtpClient::createSocket()
{
    return this->m_netWorkLayer->createSocket();
}

void NtpClient::buildClientInfo()
{
    this->m_netWorkLayer->buildClientInfo();
}

void NtpClient::changePcTime(QDateTime &datetime)
{
    qDebug()  << datetime;
    QString string = datetime.toString("yyyy-MM-dd hh:mm:ss");
    QString dateTimeString = QString("timedatectl set-time '%1'").arg(string);
    int systemDateTimeStatus= system(dateTimeString.toStdString().c_str());
    if (systemDateTimeStatus == -1)
    {
        qDebug() << "Failed to change date time";
    }
}

void NtpClient::startNtp()
{
    timer.setInterval(5000);
    QObject::connect(&this->timer, SIGNAL(timeout()), this, SLOT(getRemoteTime()));
    timer.start();
}

void NtpClient::getRemoteTime()
{
    bool flag = this->m_netWorkLayer->sendTo("getDate");
    QDateTime datetime;
    flag = flag && this->m_netWorkLayer->readFrom(datetime);
    if(flag)
        this->changePcTime(datetime);
}
