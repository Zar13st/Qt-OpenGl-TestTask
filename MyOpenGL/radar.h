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
    void receiveSatellitePosition(GLfloat,GLfloat,GLfloat);
    void setBeamR(float);

private:
    void getRadarPositionVertices();
    void getConusIndices();
    void getConusVertices(GLfloat,GLfloat,GLfloat);

    QVector<GLfloat> radarPosition; // вектор позиции радара
    QVector<GLfloat> beamConusVertices; // вектор вершин луча
    QVector<GLuint> beamConusIndices; // вектор индексов вершин луча
    QVector<GLfloat> radarBeam; //линия от радара к спутнику

    const GLuint np = 16; // число частей, на которое делится полуокружность
    const GLfloat step = M_PI / np; // шаг изменения углов

    GLfloat phiRadar = 75*M_PI/180;
    GLfloat thetaRadar = -55*M_PI/180;
    GLfloat R = 6400;

    GLfloat phiRadarBeam;
    GLfloat thetaRadarBeam;
    GLfloat rBeam = 1000;

    bool satelliteIsVisible;


};

#endif // RADAR_H
