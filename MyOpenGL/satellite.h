#ifndef SATELLITE_H
#define SATELLITE_H

#include <QVector>
#include <QtGui>
#include <math.h>

class Satellite
{
public:
    Satellite();
    ~Satellite();

    void draw();
    void move();
    GLfloat getX();
    GLfloat getY();
    GLfloat getZ();
    void setAlfa(GLfloat);
    void setBeta(GLfloat);
    void setR(GLfloat);
    void setSpeed(GLfloat);

private:
    void getVerArrays();

    const GLuint np=72; // число частей на которое делится полуокружность
    const GLfloat step = M_PI / np; // шаг изменения углов

    QVector<GLfloat> vecVertices; // вектор вершин

    GLfloat R = 8000.0f;
    GLfloat speed = 0;
    GLfloat phi= 0;
    GLfloat alfa = 0;
    GLfloat beta = 0;
    GLfloat fps = 0.025f;
};

#endif // SATELLITE_H
