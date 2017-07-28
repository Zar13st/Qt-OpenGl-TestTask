// myglwidget.h

#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <QTime>
#include <math.h>
#include "sphere.h"
#include "orbit.h"
#include "satellite.h"

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();

    const GLfloat dtMainLoop = 25.0f;

    Sphere *earth;
    Orbit *orbit;

signals:

public slots:

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
   // void mousePressEvent(QMouseEvent *event);
   // void mouseMoveEvent(QMouseEvent *event);

public slots:
    // slots for slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

    void fixedUpdate();

private:
   // QPoint lastPos;
    QTimer *mainLoopTimer;

};

#endif // MYGLWIDGET_H

