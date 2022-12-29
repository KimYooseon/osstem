#include "widget.h"

#include <QApplication>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Widget widget;
    QTest::qExec(&widget);

//    QApplication a(argc, argv);
//    Widget w;
//    w.show();
    return a.exec();
}
