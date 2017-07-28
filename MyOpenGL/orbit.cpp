#include "orbit.h"
#include "satellite.h"

Orbit::Orbit()
{
    getVerArrays();
    getIndexArray();
    satellite = new Satellite(/*this*/);
}

void Orbit::draw()
{
    glPushMatrix();
    glRotatef(alfa*180/M_PI, 1.0, 0.0, 0.0);
    glRotatef(beta*180/M_PI, 0.0, 1.0, 0.0);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor4f(1.00f, 0.00f, 0.00f, 1.0f); // цвет
    // указываем, откуда нужно извлечь данные о массиве вершин
    glVertexPointer(3, GL_FLOAT, 0, vecVertices.begin());
    // указываем, откуда нужно извлечь данные о массиве текстурных координат
    //glTexCoordPointer(2, GL_FLOAT, 0, vecTextures.begin());
    glDrawElements(GL_LINES, vecIndices.size(), GL_UNSIGNED_INT, vecIndices.begin());

    satellite->draw();

    glPopMatrix();
}

void Orbit::refresh()
{
    getVerArrays();
    getIndexArray();
}

void Orbit::getVerArrays()
{
   vecVertices.clear();
   GLfloat phi;

   for (GLuint i=0; i < 2*np+1; i++)
   {
      phi=i*step;

      vecVertices.push_back(R*sin(phi));
      vecVertices.push_back(R*cos(phi));
      vecVertices.push_back(0.0f);
   }
}

void Orbit::getIndexArray()
{
    vecIndices.clear();
    for (GLuint i=0; i < 2*np; i++)
    {
        vecIndices.push_back(i);
        vecIndices.push_back(i+1);
    }
}
