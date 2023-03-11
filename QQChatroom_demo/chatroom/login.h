#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

public:
    QMap<int, bool> ifbtn_map;//用于判断第i个按钮是否打开

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
