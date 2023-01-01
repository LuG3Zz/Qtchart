#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpSocket>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class TcpServer; }
QT_END_NAMESPACE

class TcpServer : public QWidget
{
    Q_OBJECT

public:
    TcpServer(QWidget *parent = nullptr);
     void loadConf();

    ~TcpServer();

private:
    Ui::TcpServer *ui;
    QString m_strIP;
    unsigned m_usPort;
    QTcpSocket* m_tcpSocket;
};
#endif // TCPSERVER_H
