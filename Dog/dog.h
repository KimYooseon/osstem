#ifndef DOG_H
#define DOG_H

#include <QWidget>
#include <QObject>
#include <QDebug>
#include <QTest>

class dog : public QObject
{
    Q_OBJECT

public:
    explicit dog(QObject *parent = nullptr);
    ~dog();

private slots:
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();
    void bark();
    void rollover();
    void simple();
};
#endif // DOG_H
