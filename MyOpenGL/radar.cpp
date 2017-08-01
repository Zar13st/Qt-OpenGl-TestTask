#include "radar.h"

Radar::Radar()
{
    getRadarPositionVertices();
    getConusIndices();
}

Radar::~Radar()
{

}

void Radar::draw()
{
    //маркер радара
    glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
    glVertexPointer(3, GL_FLOAT, 0, radarPosition.begin());
    glPointSize(10.0f);
    glDrawArrays(GL_POINTS, 0, radarPosition.size()/3);
    //луч радара
    if(satelliteIsVisible)
    {
        //линия
        glColor4f(1.00f, 1.00f, 0.00f, 1.0f);
        glVertexPointer(3, GL_FLOAT, 0, radarBeam.begin());
        glDrawArrays(GL_LINES, 0, radarBeam.size()/3);
        //конус
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glColor4f(1.00f, 1.00f, 0.00f, 1.0f);
        glVertexPointer(3, GL_FLOAT, 0, beamConusVertices.begin());
        glDrawElements(GL_TRIANGLES, beamConusIndices.size(), GL_UNSIGNED_INT, beamConusIndices.begin());
    }
}

void Radar::receiveSatellitePosition(GLfloat x, GLfloat y , GLfloat z)
{
    //вычисляем скалярное произведение вектора из центра земли к позиции радара и вектора от радара к спутнику
    GLfloat dotProduct = (x - radarPosition[0]) * radarPosition[0] + (y - radarPosition[1]) * radarPosition[1] + (z - radarPosition[2]) * radarPosition[2];
    //поле зрения радара - передняя полусфера
    if (dotProduct > 0) {
        satelliteIsVisible = true;
        getConusVertices(x,y,z);
    }
    else {satelliteIsVisible = false;}
}

void Radar::setBeamR(float r)
{
    rBeam = r;
}

void Radar::getRadarPositionVertices()
{
    //x,y,z радара
    radarPosition.clear();
    radarPosition.push_back(R * sin(thetaRadar) * cos(phiRadar));
    radarPosition.push_back(R * cos(thetaRadar));
    radarPosition.push_back(R * sin(thetaRadar) * sin(phiRadar));
}

void Radar::getConusIndices()
{
    beamConusIndices.clear();
    for (GLuint i=1; i < 2*np+1; i++)
    {
        beamConusIndices.push_back(0);
        beamConusIndices.push_back(i);
        beamConusIndices.push_back(i+1);
    }
}

void Radar::getConusVertices(GLfloat Xa, GLfloat Ya, GLfloat Za )
{
    //формируем вектор от радара к спутнику
    radarBeam.clear();
    radarBeam.push_back(radarPosition[0]);
    radarBeam.push_back(radarPosition[1]);
    radarBeam.push_back(radarPosition[2]);
    radarBeam.push_back(Xa);
    radarBeam.push_back(Ya);
    radarBeam.push_back(Za);
    // остриё конуса луча радара
    beamConusVertices.clear();
    beamConusVertices.push_back(radarPosition[0]);
    beamConusVertices.push_back(radarPosition[1]);
    beamConusVertices.push_back(radarPosition[2]);
    // основание конуса луча радара
    // формула взята тут - http://mathhelpplanet.com/viewtopic.php?f=33&t=34209
    GLfloat phi;
    GLfloat a = radarPosition[0] - Xa;
    GLfloat b = radarPosition[1] - Ya;
    GLfloat c = radarPosition[2] - Za;
    if (a == 0 && c == 0) {a = 0.01;}
    GLfloat r = rBeam;

    for (GLuint i=0; i < 2*np+1; i++)
    {
       phi=i*step;
       GLfloat x = radarPosition[0] - (a + r/sqrt(pow(a,2)+pow(c,2))*(c*cos(phi) - a*b*sin(phi)/sqrt(pow(a,2)+pow(b,2)+pow(c,2))));
       GLfloat y = radarPosition[1] - (b + r*sqrt(pow(a,2)+pow(c,2))*sin(phi)/sqrt(pow(a,2)+pow(b,2)+pow(c,2)));
       GLfloat z = radarPosition[2] - (c - r/sqrt(pow(a,2)+pow(c,2))-(a*cos(phi) + b*c*sin(phi)/sqrt(pow(a,2)+pow(b,2)+pow(c,2))));

       beamConusVertices.push_back(x);
       beamConusVertices.push_back(y);
       beamConusVertices.push_back(z);
    }
}
