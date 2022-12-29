#include "widget.h"
#include <QDebug>

widget::widget(QObject *parent)
    : QObject{parent}
{
    age = 0;
}

void widget::setAge(int value){
    age = value;
}

void widget::testFail(){
    QFAIL("NO REASON JUST FAIL!!!");
}

void widget::testAge(){
    if(!age) QFAIL("Age is not set!");
}

void widget::testWidget(){
    int value = 45;

    QVERIFY(age > 0 && age < 100);

    if(age > 40) QWARN("Age is over 40!");
    if(age < 21) QFAIL("Must be an adult!");

    QCOMPARE(age, value);
}
