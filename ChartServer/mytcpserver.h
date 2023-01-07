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
 public slots:
    void deleteSocket(MyTcpSocket* mysocket );//槽函数与mysocket中的信号函数offline关联，把下线的客户端从列表删除
};

#endif // MYTCPSERVER_H
