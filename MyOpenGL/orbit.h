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
    void setAlfa(GLfloat);
    void setBeta(GLfloat);
    void setR(GLfloat);

    Satellite *satellite;
private:
    void getVerArrays();
    void getIndexArray();

    const GLuint np = 72; // число частей, на которое делится полуокружность
    const GLfloat step = M_PI / np; // шаг изменения углов

    QVector<GLfloat> vecVertices; // вектор вершин
    QVector<GLuint> vecIndices; // вектор индексов вершин

    GLfloat alfa = 0;
    GLfloat beta = 0;
    GLfloat R = 8000.0f;
};

#endif // ORBIT_H
