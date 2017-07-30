#include "satellite.h"
#include "orbit.h"

Satellite::Satellite(/*const Orbit &orbit*/)
{
   // *parentOrbit = orbit;
    getVerArrays();
   // getIndexArray();
}

Satellite::~Satellite()
{
    //delete parentOrbit;
}

void Satellite::draw()
{
    glColor4f(0.00f, 1.00f, 0.00f, 1.0f);
    glVertexPointer(3, GL_FLOAT, 0, vecVertices.begin());
    glPointSize(10.0f);
    glDrawArrays(GL_POINTS, 0, vecVertices.size()/3);
}

void Satellite::move()
{
    phi+= (speed * 0.025f * 180) / (M_PI * R);
    if (phi> 2*M_PI) {phi -= 2*M_PI;}
    getVerArrays();
}

GLfloat Satellite::getX()
{
    return vecVertices[0];
}

GLfloat Satellite::getY()
{
    return vecVertices[1];
}

GLfloat Satellite::getZ()
{
    return vecVertices[2];
}

void Satellite::getVerArrays()
{
    GLfloat x,y,z,x1,y1,z1;

    vecVertices.clear();

    x1 = R*sin(phi);
    y1 = R*cos(phi)* cos(alfa);
    z1 = R*cos(phi)* sin(alfa);

    x = x1 * cos(beta) + z1 * sin(beta);
    y = y1;
    z = -x1 * sin(beta) + z1 * cos(beta);

    vecVertices.push_back(x);
    vecVertices.push_back(y);
    vecVertices.push_back(z);
}

void Satellite::getIndexArray()
{

}
