#include "opedb.h"
#include <QMessageBox>
#include <QDebug>
opeDB::opeDB(QObject *parent) : QObject(parent)
{
    //连接数据库
    m_db = QSqlDatabase::addDatabase("QMYSQL"); // 连接的数据库类型
}
opeDB &opeDB::getInstance()
{
    static opeDB instance;//定义静态对象
    return instance;//返回静态对象的引用

}

void opeDB::init()
{
    m_db.setHostName("43.136.40.227");        // 数据库服务器IP
    m_db.setUserName("root");              // 数据库用户名
    m_db.setPassword("123456");              // 数据库密码
        m_db.setDatabaseName("user_data"); // 数据库名
        if(m_db.open()) // 数据库是否打开成功
        {
            QSqlQuery query;
            query.exec("select * from userInfo");
            while(query.next())
            {
                QString data = QString("%1, %2, %3, %4").arg(query.value(0).toString()).arg(query.value(1).toString())
                                   .arg(query.value(2).toString()).arg(query.value(3).toString());
                           qDebug() << data;
            }
        }
        else
        {
            QMessageBox::critical(NULL, "数据库打开", "数据库打开失败");
        }
}



opeDB::~opeDB()
{
    m_db.close(); // 关闭数据库连接
}

bool opeDB::handleRegist(QString name, QString pwd)
{
    qDebug()<<(name.isEmpty()||pwd.isEmpty());
    if(name.isEmpty()||pwd.isEmpty()){

        return false;
    }
    QString data = QString("insert into userInfo(name,pwd) values('%1','%2');").arg(name).arg(pwd);
    qDebug()<<data;

    QSqlQuery query;
    return query.exec(data);
}

bool opeDB::handleLogin(QString name, QString pwd)
{
    if(name.isEmpty()||pwd.isEmpty()){

        return false;
    }
    QString data = QString("select * from userInfo where name='%1'and pwd='%2' and online=0 ;").arg(name).arg(pwd);
    qDebug()<<data;

    QSqlQuery query;
    query.exec(data);//执行
     if(query.next()){//next()获得结果中的每一条数据
         QString data = QString("update userInfo set online = 1 where name='%1'and pwd='%2';").arg(name).arg(pwd);
         qDebug()<<data;
         QSqlQuery query;
         query.exec(data);//执行
         return true;
     }else return false;
}

void opeDB::handleOffline(QString name)
{
    if(name.isEmpty()){
qDebug()<<"name is empty";

    }
    QString data = QString("update userInfo set online = 0 where name='%1';").arg(name);


    QSqlQuery query;
    query.exec(data);
}

