#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent,QString name);
    ~Widget();

public:
    enum Msgtype{Msg,UserEnter,UserExit};//枚举 普通信息 用户进入 用户离开
    void sendMsg(Msgtype type);//发送udp信息
    QString getUserName();//获取用户名
    QString getMsg();//获取聊天信息
    void userEnter(QString username);//处理用户进入
    void userExit(QString username,QString time);//处理用户退出
    void RecvMsg(); //接收UDP信息

private:
    Ui::Widget *ui;
    quint16 port;//端口
    QString username;//用户名
    QUdpSocket *udpSocket;//套接字

signals:
    void closeWidget();
public:
    void closeEvent(QCloseEvent *);//关闭事件
};
#endif // WIDGET_H
