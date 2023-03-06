#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

//    this->setMaximumSize(220,280);
//    this->setMinimumSize(220,280);

    this->setWindowTitle("计算器");

    QFont f("仿宋", 10);
    ui->mainLineEdit->setFont(f);

    //按钮上放图片
    QIcon con("G:\\QTPproject\\QtOnline\\calculator\\del.PNG");
    ui->delButton->setIcon(con);

    //改变按钮背景色
    ui->eqButton->setStyleSheet("background:blue");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_Button_0_clicked()
{
    expression += "0";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_Button_1_clicked()
{
    expression += "1";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_Button_2_clicked()
{
    expression += "2";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_Button_3_clicked()
{
    expression += "3";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_Button_4_clicked()
{
    expression += "4";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_Button_5_clicked()
{
    expression += "5";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_Button_6_clicked()
{
    expression += "6";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_Button_7_clicked()
{
    expression += "7";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_Button_8_clicked()
{
    expression += "8";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_Button_9_clicked()
{
    expression += "9";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_clearButton_clicked()
{
    expression.clear();
    ui->mainLineEdit->clear();
}


void Widget::on_delButton_clicked()
{
    expression.chop(1);
    ui->mainLineEdit->setText(expression);
}


void Widget::on_eqButton_clicked()
{
    typedef long long LL;

    string infix;
    string s;
    LL q[25010];
    int tt = -1;
    //把QString转换成char *
    LL tmp = 0;

    infix = expression.toStdString();

    Trans(infix, s);

    int len = s.size();

    for (int i = 0; i < len; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            int j = i + 1;
            while (s[j] >= '0' && s[j] <= '9')
            {
               j++;
            }
            j--;
            for (; i <= j; i++)
            {
                tmp = tmp * 10 + (s[i] - '0');
            }
            q[++tt] = tmp;
            tmp = 0, i = j;
        }
        else if (s[i] == ',') continue;
        else if (s[i] == '-' && s[i + 1] >= '0' && s[i + 1] <= '9')
        {
            int j = i + 1; i++;
            while (s[j] >= '1' && s[j] <= '9'){j++;}  j--;
            for (; i <= j; i++)
            {
                tmp = tmp * 10 + (s[i] - '0');
            }
            q[++tt] = tmp * -1;
            tmp = 0, i = j;
        }
        else
        {
            LL num1 = q[tt--];
            LL num2 = q[tt--];
            if (s[i] == '+') q[++tt] = num1 + num2;
            else if (s[i] == '-') q[++tt] = num2 - num1;
            else if (s[i] == '*') q[++tt] = num2 * num1;
            else if (s[i] == '/') q[++tt] = num2 / num1;
        }
    }

    ui->mainLineEdit->setText(QString::number(q[tt]));
    expression.clear();
}

int Widget::priority(char op)
{
    int priority;
    if (op == '*' || op == '/') priority = 2;
    if (op == '+' || op == '-') priority = 1;
    if (op == '(') priority = 0;
    return priority;
}


//引用符号提高转换效率
void Widget::Trans(string& str, string& str1)
{
    QStack<char> s;
    int i;
    for (i = 0; i < int(str.size()); i++)
    {
        //是数字的情况下直接输出
        if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z') || str[i] == '.')
        {
            str1 += str[i];
        }
        else //不是数字的情况分类讨论进行判断
        {
            str1 += ',';
            //栈为空时直接入栈
            if (s.empty()) s.push(str[i]);
            //左括号入栈
            else if (str[i] == '(') s.push(str[i]);
            //如果是右括号，只要栈顶不是左括号，就弹出并输出
            else if (str[i] == ')')
            {
                while (s.top() != '(')
                {
                    str1 += s.top();
                    s.pop();
                }
                //弹出左括号，但不输出
                s.pop();
            }
            else
            {
                //栈顶元素的优先级大于等于当前的运算符，就将其输出
                while (priority(str[i]) <= priority(s.top()))
                {
                    str1 += s.top();
                    s.pop();
                    //栈为空，停止
                    if (s.empty()) break;
                }
                s.push(str[i]);
            }
        }
    }
    //最后，如果不为空，就把所有的元素全部弹出
    while (!s.empty())
    {
        str1 += s.top();
        s.pop();
    }
    //str1.pop_back();
}


void Widget::on_plusButton_clicked()
{
    expression += "+";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_minusButton_clicked()
{
    expression += "-";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_multiButton_clicked()
{
    expression += "*";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_divButton_clicked()
{
    expression += "/";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_perButton_clicked()
{
    expression += "/100";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_dotButton_clicked()
{
    expression += "(";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_divButton_2_clicked()
{
    expression += ")";
    ui->mainLineEdit->setText(expression);
}

