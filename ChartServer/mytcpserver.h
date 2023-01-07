#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
#include <QTcpServer>
#include <QList>
#include "mytcpsocket.h"


class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    MyTcpServer();

    static MyTcpServer &getInstance();
    void incomingConnection(qintptr handle) override;//virtual func
private:
    QList<MyTcpSocket*> m_tcpScoketList;
};

#endif // MYTCPSERVER_H
