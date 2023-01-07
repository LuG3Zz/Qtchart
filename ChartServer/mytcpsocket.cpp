#include "mytcpsocket.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QtDebug>

MyTcpSocket::MyTcpSocket()
{

    connect(this,&MyTcpSocket::readyRead,this,&MyTcpSocket::recvMsg);
    connect(this,&MyTcpSocket::disconnected,this,&MyTcpSocket::clientOffline);
}

QString MyTcpSocket::getName()
{
    return this->m_strName;
}

void MyTcpSocket::recvMsg()
{

  qDebug()<<this->bytesAvailable();
  QByteArray byRead = this->readAll();//读取socket接受的数据
  QJsonDocument data=QJsonDocument::fromJson(byRead);//转换为Json文档

  QJsonObject msg = data.object();//转换为Json对象
  QString type = msg.value("type").toString();

  qDebug()<<(type == "register");
  //判断客户端请求类型
  if(type == "register"){
      QString id = msg.value("name").toString();
      QString pwd = msg.value("passwd").toString();

      bool ret = opeDB::getInstance().handleRegist(id,pwd);
      QJsonObject rep;
      rep.insert("type", "register_reply");

      qDebug() << rep;
      if(ret){
        rep.insert("status","success");
            //构建Json文档
         qDebug() << rep;
        QJsonDocument document;
        document.setObject(rep);
      this->write(document.toJson());

      }else{
        rep.insert("status","failure");
            //构建Json文档
        QJsonDocument document;
        document.setObject(rep);
        this->write(document.toJson());
      }
      qDebug() << rep;
  }
  if(type == "login"){
      QString id = msg.value("name").toString();
      QString pwd = msg.value("passwd").toString();

      bool ret = opeDB::getInstance().handleLogin(id,pwd);
      QJsonObject rep;
      rep.insert("type", "login_reply");

      qDebug() << rep;
      if(ret){
        rep.insert("status","success");
        this->m_strName=id;
            //构建Json文档
         qDebug() << rep;
        QJsonDocument document;
        document.setObject(rep);
      this->write(document.toJson());

      }else{
        rep.insert("status","failure");
            //构建Json文档
        QJsonDocument document;
        document.setObject(rep);
        this->write(document.toJson());
      }
      qDebug() << rep;
  }



}

void MyTcpSocket::clientOffline()
{
opeDB::getInstance().handleOffline(this->m_strName);
emit offline(this);//发送信号，把当前socket析构
}
