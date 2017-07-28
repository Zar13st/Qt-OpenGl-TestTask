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

    const GLfloat pi=3.141593;
    const GLuint np=72; // число частей, на которое делится полуокружность
    const GLfloat step=pi/np; // шаг изменения углов

    GLfloat R = 8000.0f;
    GLfloat phi= -pi;

private:
    void getVerArrays();
    void getIndexArray();

    QVector<GLfloat> vecVertices; // вектор вершин
    QVector<GLuint> vecIndices; // вектор индексов вершин

   // Orbit parentOrbit;
};

#endif // SATELLITE_H
