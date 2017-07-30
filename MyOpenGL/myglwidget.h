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
#include "radar.h"


class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();

    const GLfloat dtMainLoop = 25.0f;
signals:

public slots:

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
private slots:
    // slots for slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setOrbitRadius(int radius);
    void setSpeed(int speed);

    void fixedUpdate();

private:
    Sphere *earth;
    Orbit *orbit;
    Radar *radar;

    QTimer *mainLoopTimer;

};

#endif // MYGLWIDGET_H

