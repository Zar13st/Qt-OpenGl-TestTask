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
   // glPushMatrix();
  //  glRotatef(alfa*180/M_PI, 1.0, 0.0, 0.0);
//    glRotatef(beta*180/M_PI, 0.0, 1.0, 0.0);
   // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor4f(1.00f, 0.00f, 0.00f, 1.0f); // цвет
    // указываем, откуда нужно извлечь данные о массиве вершин
    glVertexPointer(3, GL_FLOAT, 0, vecVertices.begin());
    // указываем, откуда нужно извлечь данные о массиве текстурных координат
    //glTexCoordPointer(2, GL_FLOAT, 0, vecTextures.begin());
    glDrawElements(GL_LINES, vecIndices.size(), GL_UNSIGNED_INT, vecIndices.begin());

    satellite->draw();

  //  glPopMatrix();
}

void Orbit::refresh()
{
    getVerArrays();
   // getIndexArray();
}

void Orbit::getVerArrays()
{
   vecVertices.clear();
   GLfloat phi;

   GLfloat x,y,z,x1,y1,z1;
   for (GLuint i=0; i < 2*np+1; i++)
   {
      phi=i*step;

      x1 = R*sin(phi);
      y1 = R*cos(phi)* cos(alfa);
      z1 = R*cos(phi)* sin(alfa);

      x = x1 * cos(beta) + z1 * sin(beta);
      y = y1;
      z = -x1 * sin(beta) + z1 * cos(beta);

    /*  x1 = R * sin(phi);
      y1 = R * cos(phi) * (1 - 2 * sin(alfa/2)*sin(alfa/2));
      z1 = R * cos(phi) * 2 * sin(alfa/2)*cos(alfa/2);

      x = x1 * (1 - 2 * sin(beta/2)*sin(beta/2)) + z1 *2* sin (beta/2)* cos(beta/2);
      y = y1;
      z = x1 * 2* sin (beta/2)* cos(beta/2) + z1 * (1 - 2 * sin(beta/2)*sin(beta/2));*/


      vecVertices.push_back(x);
      vecVertices.push_back(y);
      vecVertices.push_back(z);
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
