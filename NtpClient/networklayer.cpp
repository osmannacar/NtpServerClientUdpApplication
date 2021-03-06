#include "networklayer.h"

//MSG_CONFIRM
//MSG_WAITALL
bool NetWorkLayer::readLength(int &_length)
{
    return this->readData((char *)&_length, 4);
}

bool NetWorkLayer::readData(char *data, int _length)
{
    int readed_size = ::recvfrom(this->m_sock_fd, (void *)data, _length, 0, (struct sockaddr *) &this->m_client_addr, (socklen_t*)&this->m_client_len);
    return (readed_size > 0);
}

bool NetWorkLayer::sendLength(const int _length)
{
    return this->sendData((char *)&_length, 4);
}

bool NetWorkLayer::sendData(char *data, int _length)
{
    int sended_length = ::sendto(this->m_sock_fd, (void *)data, _length, 0, (struct sockaddr *) &this->m_client_addr, this->m_client_len);
    return (sended_length > 0);
}

NetWorkLayer::NetWorkLayer(const unsigned short _port):m_port(_port)
{
    this->m_client_len = sizeof(this->m_client_addr);
}

NetWorkLayer::~NetWorkLayer()
{
    this->close();
}

bool NetWorkLayer::createSocket()
{
    this->m_sock_fd = ::socket(AF_INET, SOCK_DGRAM, 0);
    return (this->m_sock_fd > -1);
}

void NetWorkLayer::buildClientInfo()
{
    ::bzero((char *) &this->m_client_addr, sizeof(this->m_client_addr));
    this->m_client_addr.sin_family = AF_INET;
    this->m_client_addr.sin_addr.s_addr = INADDR_ANY;
    this->m_client_addr.sin_port = htons(this->m_port);
}


bool NetWorkLayer::readFrom(QString &data)
{
    int l_length;
    QByteArray array;
    bool flag = this->readLength(l_length);
    array.resize(l_length);
    flag = flag && this->readData(array.data(), l_length);
    data = QString(array);
    return flag;
}

bool NetWorkLayer::sendTo(const QString &data)
{
    int size = sizeof(data.toUtf8().data());
    return (this->sendLength(size) && this->sendData(data.toUtf8().data(), size));
}

bool NetWorkLayer::readFrom(QDateTime &time)
{
    int l_length;
    bool flag = this->readLength(l_length);
    long long tarih = time.toMSecsSinceEpoch();
    flag = flag && this->readData((char *)&tarih, l_length);
    time = QDateTime::fromMSecsSinceEpoch(tarih);
    return flag;
}

bool NetWorkLayer::sendTo(const QDateTime &time)
{
    long long tarih = time.toMSecsSinceEpoch();
    return (this->sendLength(8) && this->sendData((char*)&tarih, 8));
}

void NetWorkLayer::close()
{
    ::close(this->m_sock_fd);
}
