#include "dog.h"

#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QTest>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dog dog;
    QTest::qExec(&dog);

    return a.exec();
}
