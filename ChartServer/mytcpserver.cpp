#include "mytcpserver.h"

MyTcpServer::MyTcpServer()
{

}
MyTcpServer &MyTcpServer::getInstance()
{
    static MyTcpServer instance;
    return instance;

}

void MyTcpServer::incomingConnection(qintptr handle)//重写QTcpServer的虚函数
{

   qDebug()<<"new client connected";
   MyTcpSocket* pTcpSocket = new MyTcpSocket;
   pTcpSocket->setSocketDescriptor(handle);
   m_tcpScoketList.append(pTcpSocket);

   connect(pTcpSocket,&MyTcpSocket::offline,this,&MyTcpServer::deleteSocket);

}

void MyTcpServer::deleteSocket(MyTcpSocket *mysocket)
{
    QList<MyTcpSocket*>::iterator iter = m_tcpScoketList.begin();//使用迭代器遍历储存在List中mytcpsocket指针
    for(;iter!=m_tcpScoketList.end();iter++){
        if(mysocket==*iter)//通过迭代器获得list中的sokect的指针
        {
              (*iter)->deleteLater();//删除指针指向的对象
                m_tcpScoketList.erase(iter);//在列表中删除该指针
                break;
        }
    }
    for(int i = 0;i<m_tcpScoketList.size();i++){
        qDebug()<<m_tcpScoketList.at(i)->getName();
    }
}
