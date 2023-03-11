#include "login.h"
#include "ui_login.h"
#include <QIcon>
#include <QToolButton>
#include "widget.h"
#include <QtDebug>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    //设置图标
    this->setWindowIcon(QIcon(":/images/qq.png"));
    //设置图标
    this->setWindowTitle("chatroom 2023");

    //准备测试数据（此步骤也可以改为从数据库在线获得用户名和头像信息，此处使用离线测试数据）
    QList<QString> namelist;
    namelist<< "熏悟空" << "居八戒" << "疼三藏" << "沙僧" << "别龙马" << "奔波儿灞" << "灞波儿奔" << "犬夜叉" << "高启强";
    QStringList iconNameList;
    iconNameList << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9";

    QVector<QToolButton *> vct_btn;
    for(int i=0;i<namelist.size();i++)
    {
        QToolButton *btn = new QToolButton(this);
        QString str = QString(":/images/%1.jpg").arg(iconNameList.at(i));
        //加载图标
        btn->setIcon(QPixmap(str));
        //设置图片大小
        btn->setIconSize(QSize(100, 100));
        //设置网名
        btn->setText(namelist[i]);

        //图片透明
        btn->setAutoRaise(true);

        //设置显示格式：图片和文字一起显示
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        ui->verticalLayout->addWidget(btn);
        vct_btn.push_back(btn);

        ifbtn_map.insert(i, 0);
    }
    for(int i=0;i<namelist.size();i++)
    {
        connect(vct_btn[i],&QToolButton::clicked,[=](){
            Widget *widget = new Widget(nullptr,vct_btn[i]->text());
            widget->setWindowIcon(vct_btn[i]->icon());
            widget->setWindowTitle(vct_btn[i]->text());
            if(!ifbtn_map.value(i)){
//                qDebug() << ifbtn_map.value(i);
                widget->show();
                //修改
                ifbtn_map[i] = true;
            }
            connect(widget,&Widget::closeWidget,this,[=](){
                ifbtn_map[i] = false;
            });
        });
    }


}

Login::~Login()
{
    delete ui;
}
