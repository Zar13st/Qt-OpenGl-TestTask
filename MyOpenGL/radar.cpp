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
    glPushMatrix();
   // glRotatef(phiRadar/2, 0.0, 1.0, 0.0);
   // glRotatef(thetaRadar/2, 0.0, 0.0, 1.0);
    glColor4f(1.00f, 1.00f, 0.00f, 1.0f);
    glVertexPointer(3, GL_FLOAT, 0, vecVertices.begin());
    glDrawElements(GL_TRIANGLES, vecIndices.size(), GL_UNSIGNED_INT, vecIndices.begin());
    glPopMatrix();
}

void Radar::getVerArrays()
{
    vecRadarPos.clear();
    vecRadarPos.push_back(R * sin(thetaRadar) * cos(phiRadar));
    vecRadarPos.push_back(R * cos(thetaRadar));
    vecRadarPos.push_back(R * sin(thetaRadar) * sin(phiRadar));

    vecVertices.clear();
    vecVertices.push_back(vecRadarPos[0]);
    vecVertices.push_back(vecRadarPos[1]);
    vecVertices.push_back(vecRadarPos[2]);

    GLfloat phi;
    GLfloat rBeamEnd = sin((beamAngel/2)*(M_PI/180)) * beamLength;
    GLfloat hCircle = cos((beamAngel/2)*(M_PI/180)) * beamLength;
    for (GLuint i=0; i < 2*np+1; i++)
    {
       phi=i*step;

       vecVertices.push_back(rBeamEnd*sin(phi) + vecRadarPos[0]);
       vecVertices.push_back(0.0f + vecRadarPos[1] + hCircle);
       vecVertices.push_back(rBeamEnd*cos(phi) + vecRadarPos[2]);
    }
}

void Radar::getIndexArray()
{
    vecIndices.clear();
    for (GLuint i=1; i < 2*np; i++)
    {
        vecIndices.push_back(0);
        vecIndices.push_back(i);
        vecIndices.push_back(i+1);
    }
}
