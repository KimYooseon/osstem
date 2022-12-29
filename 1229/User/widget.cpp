#include "widget.h"
#include <QApplication>
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("parent");
    QPushButton *quit = new QPushButton("Quit", this);
    quit->setGeometry(75, 30, 62, 40);
    quit->setObjectName("child");
    connect(quit, SIGNAL(clicked()),qApp, SLOT(quit()));
    resize(200, 120);
}

Widget::~Widget()
{
}

