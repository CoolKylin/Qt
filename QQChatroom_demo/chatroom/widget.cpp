#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDateTime>
#include <QColorDialog>
#include <QFileDialog>
#include <QFont>

Widget::Widget(QWidget *parent,QString name)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    username = name;

    this->port = 8080;
    this->udpSocket=new QUdpSocket(this);

    //ShareAddress模式允许多个服务器访问同一个端口
    //ReuseAddressHint模式允许重新连接服务器
    udpSocket->bind(this->port,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);//通用模板

    //监听端口号
    connect(udpSocket,&QUdpSocket::readyRead,this,&Widget::RecvMsg);

    connect(ui->sendBtn,&QPushButton::clicked,[=](){
        sendMsg(Msg);
    });

    this->username=name;

    //有新用户加入
    sendMsg(UserEnter);

    //监听关闭按钮
    connect(ui->exitBtn,&QPushButton::clicked,[=](){
        this->close();
    });

    //字体设置
    connect(ui->fontCbx,&QFontComboBox::currentFontChanged,[=](){
        ui->msgTxtEdit->setFont(ui->fontCbx->currentFont());
        ui->msgTxtEdit->setFocus();//复原光标位置
    });

    //字体大小设置
    void (QComboBox:: * sizebtn)(const QString &text) = &QFontComboBox::currentTextChanged;
    connect(ui->sizeCbx,sizebtn,[=](const QString &text){
        ui->msgTxtEdit->setFontPointSize(text.toDouble());
        ui->msgTxtEdit->setFocus();//复原光标位置
    });

    //加粗
    connect(ui->boldTbtn,&QToolButton::clicked,this,[=](bool checked){
        if(checked)
        {
            ui->msgTxtEdit->setFontWeight(QFont::Bold);
        }
        else
        {
            ui->msgTxtEdit->setFontWeight(QFont::Normal);
        }
        ui->msgTxtEdit->setFocus();//复原光标位置
    });

    //倾斜
    connect(ui->italicTbtn,&QToolButton::clicked,this,[=](bool checked){
        ui->msgTxtEdit->setFontItalic(checked);
        ui->msgTxtEdit->setFocus();//复原光标位置
    });

    //下划线
    connect(ui->underlineTbtn,&QToolButton::clicked,this,[=](bool checked){
        ui->msgTxtEdit->setFontUnderline(checked);
        ui->msgTxtEdit->setFocus();//复原光标位置
    });

    //清空聊天记录
    connect(ui->clearTbtn,&QToolButton::clicked,this,[=](){
        ui->msgTxtEdit->clear();
    });

    //设置文本颜色
    connect(ui->colorTbtn,&QToolButton::clicked,this,[=](){
        QColor color = QColorDialog::getColor(color,this);
        ui->msgTxtEdit->setTextColor(color);
        ui->msgTxtEdit->setFocus();//复原光标位置
    });

    //保存聊天记录
    connect(ui->saveTbtn,&QToolButton::clicked,this,[=](){
        if(ui->msgBrowser->document()->isEmpty())
        {
            QMessageBox::warning(this,"警告","警告：保存内容不能为空!");
        }
        else
        {
            QString filename = QFileDialog::getSaveFileName(this,"保存聊天记录","聊天记录","(*.txt)");
            if(!filename.isEmpty())
            {
                //保存文件名称不能为空 再进行保存
                QFile file(filename);
                file.open(QIODevice::WriteOnly|QFile::Text);
                QTextStream stream(&file);
                stream << ui->msgBrowser -> toPlainText();
                file.close();
            }
        }
    });
}

void Widget::closeEvent(QCloseEvent *)
{
    emit this->closeWidget();
    sendMsg(UserExit);
    //隐藏窗体
    udpSocket->close();
    //销毁窗体
    udpSocket->destroyed();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::sendMsg(Widget::Msgtype type)
{
    QByteArray array;
    //创建流 只写模式
    QDataStream stream(&array,QIODevice::WriteOnly);
    stream << type << this->getUserName();

    switch(type)
    {
        case Msg:
            if(this->ui->msgTxtEdit->toPlainText()=="")
            {
                QMessageBox::warning(this,"警告","发送内容不能为空");
                return;
            }
            stream << this->getMsg();
            break;
        case UserEnter:

            break;
        case UserExit:

            break;
    }
    //书写报文
    udpSocket->writeDatagram(array.data(),array.size(),QHostAddress::Broadcast,this->port);


}

QString Widget::getUserName()
{
    return this->username;
}

QString Widget::getMsg()
{
    QString msg = ui->msgTxtEdit->toHtml();//返回输入的内容
    ui->msgTxtEdit->clear();//清空输入内容
    ui->msgTxtEdit->setFocus();//设置光标
    return msg;
}

void Widget::userEnter(QString username)
{
    bool isEmpty = ui->usrTblWidget->findItems(username,Qt::MatchExactly).isEmpty();
    if(isEmpty)
    {
        QTableWidgetItem *user = new QTableWidgetItem(username);
        ui->usrTblWidget->insertRow(0);
        ui->usrTblWidget->setItem(0,0,user);
        ui->msgBrowser->setTextColor(Qt::gray);
        ui->msgBrowser->append(username+"用户已上线");
        ui->userNumLbl->setText(QString("%1人在线").arg(ui->usrTblWidget->rowCount()));

        sendMsg(UserEnter);
    }
}

void Widget::userExit(QString username, QString time)
{
    bool isEmpty = ui->usrTblWidget->findItems(username,Qt::MatchExactly).isEmpty();
    if(!isEmpty)
    {
        //寻找行
        int row = ui->usrTblWidget->findItems(username,Qt::MatchExactly).first()->row();
        //移除该行
        ui->usrTblWidget->removeRow(row);
        //追加信息
        ui->msgBrowser->setTextColor(Qt::gray);
        ui->msgBrowser->append(username+"用户于" + time + "已下线");
        ui->userNumLbl->setText(QString("%1人在线").arg(ui->usrTblWidget->rowCount()));
    }
}

void Widget::RecvMsg()
{
    qint64 size = udpSocket->pendingDatagramSize();//获得数据报长度
    //qint64转int
    int msgSize = static_cast<int>(size);
    QByteArray array = QByteArray(msgSize,0);//初始化所有数据为0
    udpSocket->readDatagram(array.data(),size);//读取数据报
    //创建流 只读模式
    QDataStream stream(&array,QIODevice::ReadOnly);

    int msgtype;
    stream >> msgtype;//读取类型

    QString name,msg;//用户名，聊天信息
    QString time = QDateTime::currentDateTime().toString("yyyy--mm-dd hh:mm:ss");

    switch(msgtype)
    {
        case Msg://普通聊天
            stream >> name >> msg;//流出姓名和聊天内容
            //增加聊天记录
            ui->msgBrowser->setTextColor(Qt::blue);
//            ui->msgBrowser->setCurrentFont("Times New Roman",12);
            ui->msgBrowser->append("["+name+"]"+time);
            ui->msgBrowser->append(msg);
            break;
        case UserEnter:
            stream>>name;
            userEnter(name);
            break;
        case UserExit:
            stream>>name;
            userExit(name,time);
            break;
    }
}

