#include "widget.h"

#include <QApplication>
#include "login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login b;
    b.show();

    return a.exec();
}
