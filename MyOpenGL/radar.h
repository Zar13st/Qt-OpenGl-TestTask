#ifndef RADAR_H
#define RADAR_H

#include <QVector>
#include <QtGui>
#include <math.h>

class Radar
{
public:
    Radar();
    ~Radar();

    void draw();
    void scane();

private:
    void getVerArrays();
    void getIndexArray();

    QVector<GLfloat> vecRadarPos; // вектор позиции радара
    QVector<GLfloat> vecVertices; // вектор вершин луча
    QVector<GLuint> vecIndices; // вектор индексов вершин луча

    const GLuint np = 16; // число частей, на которое делится полуокружность
    const GLfloat step = M_PI / np; // шаг изменения углов

    GLfloat phiRadar = 90*M_PI/180;
    GLfloat thetaRadar = -55*M_PI/180;
    GLfloat R = 6400;
    GLfloat phiRadarBeam = 90*M_PI/180;
    GLfloat thetaRadarBeam = -55*M_PI/180;
    GLfloat beamAngel = 25.0f;
    GLfloat beamLength = 4000;

};

#endif // RADAR_H
