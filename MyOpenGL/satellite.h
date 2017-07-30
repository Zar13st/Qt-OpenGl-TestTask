#ifndef SATELLITE_H
#define SATELLITE_H

#include <QVector>
#include <QtGui>
#include <math.h>
#include "sceneobjects.h"

class Satellite
{
    friend Orbit;
public:
    Satellite();
   //Satellite(const Orbit&);
    ~Satellite();

    void draw();
    void move();
    GLfloat getX();
    GLfloat getY();
    GLfloat getZ();

    const GLuint np=72; // число частей, на которое делится полуокружность
    const GLfloat step = M_PI / np; // шаг изменения углов

    GLfloat R = 8000.0f;
    GLfloat speed = 0;
    GLfloat phi= 0;
    GLfloat alfa = 0;
    GLfloat beta = 0;

private:
    void getVerArrays();
    void getIndexArray();

    QVector<GLfloat> vecVertices; // вектор вершин
    QVector<GLuint> vecIndices; // вектор индексов вершин

  //  Orbit *parentOrbit;
};

#endif // SATELLITE_H
