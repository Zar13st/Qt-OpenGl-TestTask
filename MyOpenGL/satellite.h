#ifndef SATELLITE_H
#define SATELLITE_H

#include <QVector>
#include <QtGui>
#include <math.h>
//#include "orbit.h"

class Satellite
{
public:
    Satellite();
  //  Satellite(const Orbit);
    ~Satellite();

    void draw();
    void move();

    const GLuint np=72; // число частей, на которое делится полуокружность
    const GLfloat step = M_PI / np; // шаг изменения углов

    GLfloat R = 8000.0f;
    GLfloat speed = 0;
    GLfloat phi= - M_PI;

private:
    void getVerArrays();
    void getIndexArray();

    QVector<GLfloat> vecVertices; // вектор вершин
    QVector<GLuint> vecIndices; // вектор индексов вершин

    //Orbit parentOrbit;
};

#endif // SATELLITE_H
