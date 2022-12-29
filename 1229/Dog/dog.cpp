#include "dog.h"

dog::dog(QObject *parent)
    : QObject(parent)
{
    qInfo() << "Constructor";
}

void dog::initTestCase() {
    qInfo() << "initTestCase";
}

void dog::init(){
    qInfo()<<"init";
}

void dog::cleanup(){
    qInfo()<<"cleanup";
}

void dog::cleanupTestCase(){
    qInfo()<<"cleanupTestCase";
}

void dog::bark(){
    qInfo()<<"bark bark bark";
}

void dog::rollover(){
    qInfo()<<"rolls";
}

void dog::simple(){
    QString str1 = QLatin1String("This is a test string");
    QString str2 = QLatin1String("This is a test string");
    QCOMPARE(str1.localeAwareCompare(str2), 0);
    QBENCHMARK_ONCE{
        str1.localeAwareCompare(str2);
    }
}

dog::~dog()
{
}

