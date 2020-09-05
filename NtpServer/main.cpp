#include <QCoreApplication>
#include <ntpserver.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    NtpServer ntpServer(1234);
    if(ntpServer.createSocket()){
        ntpServer.buildServerInfo();
        if(ntpServer.bindServer())
            ntpServer.listen();
    }

    return a.exec();
}

