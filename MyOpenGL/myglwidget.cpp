// myglwidget.cpp

#include <QtWidgets>
#include <QtOpenGL>
#include <GL/glext.h>

#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    earth = new Sphere();
    orbit = new Orbit();
}

MyGLWidget::~MyGLWidget()
{
    delete earth;
    delete orbit;
}

QSize MyGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize MyGLWidget::sizeHint() const
{
    return QSize(400, 400);
}

void MyGLWidget::setXRotation(int angle)
{
     orbit->alfa =orbit->pi * (float)angle/180.0f;
     updateGL();
}

void MyGLWidget::setYRotation(int angle)
{
    orbit->beta =orbit->pi * (float)angle/180.0f;
    updateGL();
}

void MyGLWidget::setZRotation(int angle)
{
    orbit->R =angle;
    orbit->refresh();
    updateGL();
}

void MyGLWidget::initializeGL()
{
    qglClearColor(Qt::black);
    glEnable(GL_DEPTH_TEST); // проверка глубины пикселя
    glShadeModel(GL_FLAT);
   glEnable(GL_CULL_FACE);

 //   glEnable(GL_TEXTURE_2D); // установить режим двумерных текстур


    glEnableClientState(GL_VERTEX_ARRAY);
   // glEnableClientState(GL_TEXTURE_COORD_ARRAY);  // активизируем массив текстурных координат

    // источник света
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    //static GLfloat lightPosition[4] = { 3, 3, 3, 1 };
    //glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка буфера изображения и глубины
    glMatrixMode(GL_MODELVIEW); // устанавливаем положение и ориентацию матрице моделирования
    glLoadIdentity(); // загружаем единичную матрицу моделирования
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glScalef(1, 1, 1); // масштабирование по осям
    earth->draw();
    orbit->draw();
}

void MyGLWidget::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION); // устанавливаем текущей проекционную матрицу
        glLoadIdentity(); // присваиваем проекционной матрице единичную матрицу
        GLfloat ratio=(GLfloat)nHeight/(GLfloat)nWidth;
        if (nWidth>=nHeight)
            glOrtho(-10000.0/ratio, 10000.0/ratio, -10000.0, 10000.0, 10000.0, -10000.0);
        else
            glOrtho(-10000.0, 10000.0, -10000.0*ratio, 10000.0*ratio, 10000.0, -10000.0);
            glViewport(0, 0, (GLint)nWidth, (GLint)nHeight); // устанавливаем видовое окно с размерами равными окну виджета
}
/*
void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
       // setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
      //  setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }

    lastPos = event->pos();
}*/

