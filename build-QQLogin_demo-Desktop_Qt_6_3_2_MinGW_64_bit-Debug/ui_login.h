/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QLabel *labtop;
    QWidget *widget;
    QPushButton *btnRegister;
    QPushButton *btnQrcode;
    QPushButton *btnLogin;
    QComboBox *username;
    QLineEdit *passwd;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QPushButton *pushButton;
    QPushButton *btnMin;
    QPushButton *btnClose;
    QLabel *labportrait;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QString::fromUtf8("Login"));
        Login->resize(430, 330);
        Login->setMinimumSize(QSize(430, 330));
        Login->setMaximumSize(QSize(430, 330));
        Login->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	background-color: rgb(144, 255, 246);\n"
"}\n"
".QWidget\n"
"{\n"
"	background-color:rgb(255, 255, 255)\n"
"}\n"
"QPushButton\n"
"{\n"
"	border:one;\n"
"}\n"
"QPushButton#btnMin\n"
"{\n"
"	\n"
"	image: url(:/images/min.png);\n"
"}\n"
"QPushButton#btnClose\n"
"{\n"
"	\n"
"	image: url(:/images/close.png);\n"
"}\n"
"QPushButton#btnMin:hover\n"
"{\n"
"	background-color:rgba(190,190,190,200); \n"
"}\n"
"QPushButton#btnClose:hover\n"
"{\n"
"	background-color:rgb(255,84,57);\n"
"}\n"
"QPushButton#btnLogin\n"
"{\n"
"	background-color:rgb(23,196,252);\n"
"	border-radius:5px;\n"
"	font:normal 15px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	color:white;\n"
"}\n"
"QPushButton#btnQrcode\n"
"{\n"
"	image:url(:/images/qrcode.png)\n"
"}\n"
"QPushButton#btnQrcode:hover\n"
"{\n"
"	image:url(:/images/qrcode-hover.png)\n"
"}\n"
"QComboBox,QLineEdit\n"
"{\n"
"	border:none;\n"
"	border-bottom:1px solid rgb(229,229,229);\n"
"	font:normal  \"\345\256\213\344\275\223\";\n"
"	color:rgb(154,154,154);\n"
""
                        "}\n"
"QComboBox:hover,QLineEdit:hover\n"
"{\n"
"	border-bottom:1px solid rgb(193,193,193)\n"
"}\n"
"QComboBox:focus,QLineEdit:focus\n"
"{\n"
"	border-bottom:1px solid rgb(18,183,245)\n"
"}\n"
"QComboBox::drop-down\n"
"{\n"
"	min-width:25px;\n"
"	border-image:url(:/images/drop-down.png)\n"
"}\n"
"QComboBox::drop-down:hover\n"
"{\n"
"	border-image:url(:/images/drop-down-hover.png)\n"
"}\n"
"QComboBox::drop-down:checked\n"
"{\n"
"	border-image:url(:/images/drop-down-on-hover.png)\n"
"}\n"
"QLabel#labportrait\n"
"{\n"
"	min-width:70px;\n"
"	min-height:70px;\n"
"	max-width:70px;\n"
"	max-height:70px;\n"
"	border-radius:35px;\n"
"	border:1px solid white;\n"
"	background:white\n"
"}"));
        labtop = new QLabel(Login);
        labtop->setObjectName(QString::fromUtf8("labtop"));
        labtop->setGeometry(QRect(0, 0, 431, 124));
        labtop->setMinimumSize(QSize(0, 124));
        labtop->setMaximumSize(QSize(16777215, 124));
        labtop->setPixmap(QPixmap(QString::fromUtf8(":/images/gif_label.gif")));
        widget = new QWidget(Login);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 124, 430, 206));
        btnRegister = new QPushButton(widget);
        btnRegister->setObjectName(QString::fromUtf8("btnRegister"));
        btnRegister->setGeometry(QRect(0, 180, 75, 24));
        btnQrcode = new QPushButton(widget);
        btnQrcode->setObjectName(QString::fromUtf8("btnQrcode"));
        btnQrcode->setGeometry(QRect(390, 170, 32, 32));
        btnLogin = new QPushButton(widget);
        btnLogin->setObjectName(QString::fromUtf8("btnLogin"));
        btnLogin->setGeometry(QRect(90, 160, 240, 35));
        username = new QComboBox(widget);
        username->setObjectName(QString::fromUtf8("username"));
        username->setGeometry(QRect(90, 50, 240, 30));
        username->setEditable(true);
        passwd = new QLineEdit(widget);
        passwd->setObjectName(QString::fromUtf8("passwd"));
        passwd->setGeometry(QRect(90, 90, 240, 30));
        widget1 = new QWidget(widget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(90, 130, 241, 22));
        horizontalLayout = new QHBoxLayout(widget1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        checkBox = new QCheckBox(widget1);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout->addWidget(checkBox);

        checkBox_2 = new QCheckBox(widget1);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        horizontalLayout->addWidget(checkBox_2);

        pushButton = new QPushButton(widget1);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        btnMin = new QPushButton(Login);
        btnMin->setObjectName(QString::fromUtf8("btnMin"));
        btnMin->setGeometry(QRect(370, 0, 31, 31));
        btnClose = new QPushButton(Login);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setGeometry(QRect(400, 0, 31, 31));
        labportrait = new QLabel(Login);
        labportrait->setObjectName(QString::fromUtf8("labportrait"));
        labportrait->setGeometry(QRect(180, 80, 72, 72));
        labportrait->setMinimumSize(QSize(72, 72));
        labportrait->setMaximumSize(QSize(72, 72));
        labportrait->setTextFormat(Qt::AutoText);
        labportrait->setPixmap(QPixmap(QString::fromUtf8(":/images/portrait/rekkles.jpg")));
        labportrait->setScaledContents(true);
        labportrait->setWordWrap(false);

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Login", nullptr));
        labtop->setText(QString());
        btnRegister->setText(QCoreApplication::translate("Login", "\346\263\250\345\206\214\350\264\246\345\217\267", nullptr));
        btnQrcode->setText(QString());
        btnLogin->setText(QCoreApplication::translate("Login", "\345\256\211\345\205\250\347\231\273\345\275\225", nullptr));
        passwd->setPlaceholderText(QCoreApplication::translate("Login", "\345\257\206\347\240\201", nullptr));
        checkBox->setText(QCoreApplication::translate("Login", "\350\207\252\345\212\250\347\231\273\345\275\225", nullptr));
        checkBox_2->setText(QCoreApplication::translate("Login", "\350\256\260\344\275\217\345\257\206\347\240\201", nullptr));
        pushButton->setText(QCoreApplication::translate("Login", "\346\211\276\345\233\236\345\257\206\347\240\201", nullptr));
        btnMin->setText(QString());
        btnClose->setText(QString());
        labportrait->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
