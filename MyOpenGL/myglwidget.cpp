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

    mainLoopTimer = new QTimer();
    connect(mainLoopTimer, SIGNAL(timeout()), this, SLOT(fixedUpdate()));
    mainLoopTimer->start(dtMainLoop);
}

MyGLWidget::~MyGLWidget()
{
    delete earth;
    delete orbit;
    delete mainLoopTimer;
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
     orbit->alfa =M_PI * (float)angle/180.0f;
}

void MyGLWidget::setYRotation(int angle)
{
    orbit->beta =M_PI * (float)angle/180.0f;
}

void MyGLWidget::setZRotation(int radius)
{
    orbit->R =radius;
    orbit->satellite->R=radius;
    orbit->refresh();
}

void MyGLWidget::fixedUpdate()
{
    orbit->satellite->move();
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


