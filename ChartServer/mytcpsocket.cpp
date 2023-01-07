#include "mytcpsocket.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QtDebug>
MyTcpSocket::MyTcpSocket()
{

    connect(this,&MyTcpSocket::readyRead,this,&MyTcpSocket::recvMsg);
}

void MyTcpSocket::recvMsg()
{

  qDebug()<<this->bytesAvailable();
  QByteArray ba;
  ba=this->readAll();
  QJsonDocument data=QJsonDocument::fromJson(ba);
  QJsonObject msg = data.object();
  QJsonValue value = msg.value("msg");
  QJsonValue id = msg.value("id");
  QJsonValue pwd = msg.value("passwd");
  qDebug()<<value.toString()<<Qt::endl;
  qDebug()<<id.toString()<<Qt::endl;
  qDebug()<<pwd.toString()<<Qt::endl;




}
