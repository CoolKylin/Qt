#include "login.h"
#include "ui_login.h"
#include <QMovie>

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
    , m_label(new QLabel)
{
    //去掉边框
    setWindowFlags(Qt::WindowType::FramelessWindowHint);
    //背景透明
    setAttribute(Qt::WA_TranslucentBackground);

    ui->setupUi(this);

    //给labtop设置动画
    QMovie * movie = new QMovie(this); //用来播放gif图片
    movie->setFileName(":/images/gif_label.gif");
    movie->start();//在内存里播放
    ui->labtop->setMovie(movie);

    //usrname提示
    ui->username->lineEdit()->setPlaceholderText("QQ号码/手机/邮箱");

    m_label->setPixmap(QPixmap("://images/kylin.png"));
    m_label->resize(300,300);
    m_label->setScaledContents(true);
}

Login::~Login()
{
    delete ui;
}


void Login::on_btnMin_clicked()
{
    //最小化窗口
    this->showMinimized();
}


void Login::on_btnClose_clicked()
{
    //最小化窗口
    this->close();
}

//点击登录按钮处理函数
void Login::on_btnLogin_clicked()
{
    //关闭当前窗口
    this->hide();
    //显示label
    m_label->show();
}

