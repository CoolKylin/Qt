#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_btnMin_clicked();

    void on_btnClose_clicked();

    void on_btnLogin_clicked();

private:
    Ui::Login *ui;
    QLabel * m_label;
};
#endif // LOGIN_H
