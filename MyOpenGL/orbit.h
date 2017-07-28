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

    const GLuint np = 72; // число частей, на которое делится полуокружность
    const GLfloat step = M_PI / np; // шаг изменения углов

    GLfloat alfa = - M_PI;
    GLfloat beta = - M_PI;
    GLfloat R = 8000.0f;


    Satellite *satellite;
private:
    void getVerArrays();
    void getIndexArray();

    QVector<GLfloat> vecVertices; // вектор вершин
    QVector<GLuint> vecIndices; // вектор индексов вершин
};

#endif // ORBIT_H
