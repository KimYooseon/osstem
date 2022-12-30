#include "dog.h"
#include "widget.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QTest>



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    widget widget;
    widget.setAge(0);
    QTest::qExec(&widget);

    //QApplication a(argc, argv);
    //dog dog;
    //QTest::qExec(&dog);

    return a.exec();
}
