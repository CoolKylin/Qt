#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStack>
#include <cstring>
#include <QString>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_Button_1_clicked();

    void on_Button_2_clicked();

    void on_Button_3_clicked();

    void on_Button_4_clicked();

    void on_Button_5_clicked();

    void on_Button_6_clicked();

    void on_Button_7_clicked();

    void on_Button_8_clicked();

    void on_Button_0_clicked();

    void on_Button_9_clicked();

    void on_clearButton_clicked();

    void on_delButton_clicked();

    void on_eqButton_clicked();

    void on_plusButton_clicked();

    void on_minusButton_clicked();

    void on_multiButton_clicked();

    void on_divButton_clicked();

    void on_perButton_clicked();

    void on_dotButton_clicked();

    void on_divButton_2_clicked();

private:
    Ui::Widget *ui;
    QString expression;
    int priority(char op);
    void Trans(string& str, string& str1);
};

#endif // WIDGET_H
