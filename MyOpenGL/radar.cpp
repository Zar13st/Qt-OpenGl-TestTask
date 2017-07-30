#include "radar.h"

Radar::Radar()
{
    getVerArrays();
    getIndexArray();
}

Radar::~Radar()
{

}

void Radar::draw()
{
    //маркер радара
    glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
    glVertexPointer(3, GL_FLOAT, 0, vecRadarPos.begin());
    glPointSize(10.0f);
    glDrawArrays(GL_POINTS, 0, vecRadarPos.size()/3);
    //луч радара
    if(satelliteIsVisible)
    {
        glColor4f(1.00f, 1.00f, 0.00f, 1.0f);
        glVertexPointer(3, GL_FLOAT, 0, vecBeam.begin());
        glDrawArrays(GL_LINES, 0, vecBeam.size()/3);
    }


  /*  //луч радара ввиде конуса
    glPushMatrix();

    glRotatef(phiRadar*180/M_PI, 1.0, 0.0, 0.0);
    glRotatef(thetaRadar*180/M_PI, 0.0, 1.0, 0.0);

  //  glTranslatef(vecRadarPos[0], vecRadarPos[1], vecRadarPos[2]);
    glColor4f(1.00f, 1.00f, 0.00f, 1.0f);
    glVertexPointer(3, GL_FLOAT, 0, vecVertices.begin());
    glDrawElements(GL_TRIANGLES, vecIndices.size(), GL_UNSIGNED_INT, vecIndices.begin());
    glPopMatrix();*/
}

void Radar::setSatellitePosition(GLfloat x, GLfloat y , GLfloat z)
{
    //вычисляем скалярное произведение вектора из центра земли к позиции радара и вектора от радара к спутнику
    GLfloat dotProduct = (x - vecRadarPos[0]) * vecRadarPos[0] + (y - vecRadarPos[1]) * vecRadarPos[1] + (z - vecRadarPos[2]) * vecRadarPos[2];
    //поле зрения радара - передняя полусфера
    if (dotProduct > 0) {satelliteIsVisible = true;}
    else {satelliteIsVisible = false;}
    //формируем вектор от радара к спутнику
    vecBeam.clear();
    vecBeam.push_back(vecRadarPos[0]);
    vecBeam.push_back(vecRadarPos[1]);
    vecBeam.push_back(vecRadarPos[2]);
    vecBeam.push_back(x);
    vecBeam.push_back(y);
    vecBeam.push_back(z);
}

void Radar::getVerArrays()
{
    //x,y,z радара
    vecRadarPos.clear();
    vecRadarPos.push_back(R * sin(thetaRadar) * cos(phiRadar));
    vecRadarPos.push_back(R * cos(thetaRadar));
    vecRadarPos.push_back(R * sin(thetaRadar) * sin(phiRadar));
    // остриё конуса луча радара
    vecVertices.clear();
    vecVertices.push_back(0);
    vecVertices.push_back(0);
    vecVertices.push_back(0);
    // основание конуса луча радара
    GLfloat phi;
    GLfloat rBeamEnd = sin((beamAngel/2)*(M_PI/180)) * beamLength;
    GLfloat hCircle = cos((beamAngel/2)*(M_PI/180)) * beamLength;
    for (GLuint i=0; i < 2*np+1; i++)
    {
       phi=i*step;

       vecVertices.push_back(rBeamEnd*sin(phi));
       vecVertices.push_back(rBeamEnd*cos(phi));
       vecVertices.push_back(-hCircle);
    }
}

void Radar::getIndexArray()
{
    vecIndices.clear();
    for (GLuint i=1; i < 2*np+1; i++)
    {
        vecIndices.push_back(0);
        vecIndices.push_back(i);
        vecIndices.push_back(i+1);
    }
}
