#include <math.h>
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    //setWindowTitle("Hello OpenGL");
    //resize(600, 600);
    radius = 0.05;
    delta_theta = 2*M_PI/20;
    theta = 0.0;
    cord_length = 0.5;

    setWindowTitle("OpenGL Animation");
    resize(600, 600);

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), SLOT(timerFunction()));
    timer->start(1000/60);
}

Widget::~Widget()
{
}

void Widget::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void Widget::resizeGL(int w, int h){
    glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
}


void Widget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);
    current_angle = cos(0.1*atime);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);
    xcenter = -cord_length*sin(current_angle);
    ycenter = -cord_length*cos(current_angle);
    glVertex2f(xcenter, ycenter);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    theta = 0;
    while(theta <= 2*M_PI){
        x = xcenter + radius * sin(theta);
        y = ycenter + radius * cos(theta);
        glVertex2f(x, y);
        theta += delta_theta;
    };
    glEnd();

//    glBegin(GL_POLYGON);
//    glVertex3f(0.25, 0.25, 0.0);
//    glVertex3f(0.75, 0.25, 0.0);
//    glVertex3f(0.75, 0.75, 0.0);
//    glVertex3f(0.25, 0.75, 0.0);

//    glFlush();
}

void Widget::timerFunction()
{
    atime++;
    update();
}
