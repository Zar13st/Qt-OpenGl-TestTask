#include "orbit.h"

Orbit::Orbit()
{
    getVerArrays();
    getIndexArray();
    satellite = new Satellite();
}

void Orbit::draw()
{
    glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
    glVertexPointer(3, GL_FLOAT, 0, vecVertices.begin());
    glDrawElements(GL_LINES, vecIndices.size(), GL_UNSIGNED_INT, vecIndices.begin());

    satellite->draw();
}

void Orbit::refresh()
{
    getVerArrays();
}

void Orbit::setAlfa(GLfloat alfa)
{
    this->alfa = alfa;
}

void Orbit::setBeta(GLfloat beta)
{
    this->beta = beta;
}

void Orbit::setR(GLfloat R)
{
    this->R = R;
}

void Orbit::getVerArrays()
{
   vecVertices.clear();
   GLfloat phi;

   GLfloat X,Y,Z;
   GLfloat XafterOXrot, YafterOXrot, ZafterOXrot;
   GLfloat XafterOYrot, YafterOYrot, ZafterOYrot;
   for (GLuint i=0; i < 2*np+1; i++)
   {
      phi=i*step;
      //стартовая орбита
      X = R*sin(phi);
      Y = R*cos(phi);
      Z = 0;
      //орбита после поворота вокруг ОХ, используем матрицу поворота
      XafterOXrot = 1 * X + 0 * Y + 0 * Z;
      YafterOXrot = 0 * X + cos(alfa) * Y + -sin(alfa) * Z;
      ZafterOXrot = 0 * X + sin(alfa) * Y + cos(alfa) * Z;
      //орбита после поворота вокруг ОY, используем матрицу поворота
      XafterOYrot = cos(beta) * XafterOXrot + 0 * YafterOXrot + sin(beta) * ZafterOXrot;
      YafterOYrot = 0 * XafterOXrot + 1 * YafterOXrot + 0 * ZafterOXrot;
      ZafterOYrot = -sin(beta) * XafterOXrot + 0 * YafterOXrot + cos(beta) * ZafterOXrot;

      vecVertices.push_back(XafterOYrot);
      vecVertices.push_back(YafterOYrot);
      vecVertices.push_back(ZafterOYrot);
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
