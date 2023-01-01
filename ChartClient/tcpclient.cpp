#include "tcpclient.h"
#include "ui_tcpclient.h"

#include <QDebug>
#include <QFile>
#include <QHostAddress>
#include <QMessageBox>

TcpClient::TcpClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    loadConf();
    connect(m_tcpSocket,&QTcpSocket::connected,this,&TcpClient::showConnect);
    m_tcpSocket->connectToHost(QHostAddress(m_strIP),m_usPort);
}

TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::loadConf()
{
   QFile file(":/client.conf");
   if(file.open(QIODevice::ReadOnly)){
      QByteArray baData=file.readAll();
      //QString strData= (char*)&baData;
      QString strData= baData.toStdString().c_str();
      file.close();
      strData.replace("\n"," ");
      QStringList strlist = strData.split(" ");
      qDebug()<<strData;
      m_strIP = strlist.at(0);
      m_usPort = strlist.at(1).toUShort();
      qDebug()<<"ip:"<<m_strIP<<"port:"<<m_usPort;

   }
   else{
       QMessageBox::critical(this,"open config","open conf error");
   }


}

void TcpClient::showConnect()
{
 QMessageBox::information(this,"连接服务器","连接服务器成功");
}

