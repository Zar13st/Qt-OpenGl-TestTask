#include "satellite.h"

Satellite::Satellite(/*const Orbit orbit*/)
{
   // parentOrbit = orbit;
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

void Satellite::getVerArrays()
{
    vecVertices.clear();
    vecVertices.push_back(R * sin(phi));
    vecVertices.push_back(R * cos(phi));
    vecVertices.push_back(0.0f);
}

void Satellite::getIndexArray()
{

}
