#ifndef ORBIT_H
#define ORBIT_H

#include <QVector>
#include <QtGui>
#include <math.h>
#include "satellite.h"

class Orbit
{
public:
    Orbit();

    void draw();
    void refresh();

    const GLfloat pi=3.141593;
    const GLuint np=72; // число частей, на которое делится полуокружность
    const GLfloat step=pi/np; // шаг изменения углов

    GLfloat alfa = -pi;
    GLfloat beta = -pi;
    GLfloat R = 8000.0f;


    Satellite *satellite;
private:
    void getVerArrays();
    void getIndexArray();

    QVector<GLfloat> vecVertices; // вектор вершин
    QVector<GLuint> vecIndices; // вектор индексов вершин
};

#endif // ORBIT_H
