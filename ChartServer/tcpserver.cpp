#include "tcpserver.h"
#include "ui_tcpserver.h"
#include "mytcpserver.h"
#include <QDebug>
#include <QFile>
#include <QHostAddress>
#include <QMessageBox>

TcpServer::TcpServer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpServer)
{
    ui->setupUi(this);
    loadConf();
    MyTcpServer::getInstance().listen(QHostAddress::Any,m_usPort);
}

void TcpServer::loadConf()
{
    QFile file(":/Server.conf");
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

TcpServer::~TcpServer()
{
    delete ui;

}
