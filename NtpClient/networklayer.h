#ifndef NETWORKLAYER_H
#define NETWORKLAYER_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <QString>
#include <QDateTime>

class NetWorkLayer
{
    int m_sock_fd; /* socket */
    unsigned short m_port; /* port to listen on */
    int m_client_len; /* byte size of client's address */
    struct sockaddr_in m_client_addr; /* client addr */
    struct hostent *m_hostp; /* client host info */
    QString m_client_ip; /* dotted decimal host addr string */
    int m_opt = 1; /* flag value for setsockopt */

    bool readLength(int &_length);
    bool readData(char *data, int _length);
    bool sendLength(const int _length);
    bool sendData(char *data, int _length);
public:
    NetWorkLayer(const unsigned short _port);
    ~NetWorkLayer();
    bool createSocket();
    void buildClientInfo();
    bool readFrom(QString &data);
    bool sendTo(const QString &data);
    bool readFrom(QDateTime &time);
    bool sendTo(const QDateTime &time);
    void close();
};

#endif // NETWORKLAYER_H

