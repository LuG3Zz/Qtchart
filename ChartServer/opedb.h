#ifndef OPEDB_H
#define OPEDB_H
#include <QObject>
#include <QSqlDatabase>//连接数据库导入
#include <QSqlQuery> //查询数据库导入
#include <QMessageBox>
#include <QDebug>
#include <QObject>

class opeDB : public QObject
{
    Q_OBJECT
public:
    explicit opeDB(QObject *parent = 0);

    static opeDB& getInstance(); // 公用获取引用，实现单例模式
    void init(); // 初始化函数，数据库连接
        ~opeDB(); // 析构函数，关闭数据库连接
    bool handleRegist(QString name,QString pwd);
    bool handleLogin(QString name,QString pwd);
    void handleOffline(QString name);
signals:

private:
    QSqlDatabase m_db;//连接数据库
public slots:
};

#endif // OPEDB_H
