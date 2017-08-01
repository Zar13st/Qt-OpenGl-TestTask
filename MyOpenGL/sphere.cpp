#include "sphere.h"

Sphere::Sphere()
{
    getVerTexArrays();
    getIndexArray();
    genTexture();
}

Sphere::~Sphere()
{

}

void Sphere::draw()
{
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindTexture(GL_TEXTURE_2D, textureID[0]);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor4f(1.00f, 1.00f, 1.00f, 1.0f);

    glPushMatrix();
    glRotatef(-90, 1.0, 0.0, 0.0);
    glVertexPointer(3, GL_FLOAT, 0, vecVertices.begin());
    glTexCoordPointer(2, GL_FLOAT, 0, vecTextures.begin());
    glDrawElements(GL_TRIANGLES, vecIndices.size(), GL_UNSIGNED_INT, vecIndices.begin());
    glPopMatrix();

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Sphere::getVerTexArrays()
{
   GLfloat R=6400.0f; // радиус сферы
   GLfloat phi, theta; // углы фи и тэта

   // двойной цикл по углам
   for (GLuint i=0; i < 2*np+1; i++)
   {
      phi=i*step; // изменение угла фи

      for (GLuint j=0; j < np+1; j++)
      {
         theta=j*step; // изменение угла тэта

         if (j==0) // вершины "северный полюс"
         {
            if (i<2*np)
            {
               // добавляем в конец вектора:
               vecVertices.push_back(0.0f);
               vecVertices.push_back(0.0f);
               vecVertices.push_back(R);

               vecTextures.push_back((phi+step/2)/(2*M_PI)); // текстурная x-координата вершины
               vecTextures.push_back(1.0f);                // текстурная y-координата вершины
            }
         }
         else
         {
            if (j<np) // вершины между северными и южными полюсами
            {
               if (i<2*np)
               {
                  vecVertices.push_back(R*sin(theta)*cos(phi));
                  vecVertices.push_back(R*sin(theta)*sin(phi));
                  vecVertices.push_back(R*cos(theta));

                  vecTextures.push_back(phi/(2*M_PI));
               }
               else
               {
                  vecVertices.push_back(R*sin(theta));
                  vecVertices.push_back(0.0f);
                  vecVertices.push_back(R*cos(theta));

                  vecTextures.push_back(1.0f);
               }
               vecTextures.push_back((M_PI-theta)/M_PI);
            }
            else // вершины "южный полюс"
            {
               if (i<2*np)
               {
                  vecVertices.push_back(0.0f);
                  vecVertices.push_back(0.0f);
                  vecVertices.push_back(-R);

                  vecTextures.push_back((phi+step/2)/(2*M_PI));
                  vecTextures.push_back(0.0f);
               }
            }
         }
      }
   }
}

void Sphere::getIndexArray()
{
   for (GLuint i=0; i < 2*np; i++)
   {
      for (GLuint j=0; j < np; j++)
      {
         if (j==0)
         {
            vecIndices.push_back(i*(np+1));
            vecIndices.push_back(i*(np+1)+1);
            if (i<(2*np-1))
               vecIndices.push_back((i+1)*(np+1)+1);
            else
               vecIndices.push_back((i+1)*(np+1));
         }
         else
         {
            if (j<(np-1))
            {
               if (i<(2*np-1))
               {
                  vecIndices.push_back(i*(np+1)+j);
                  vecIndices.push_back((i+1)*(np+1)+(j+1));
                  vecIndices.push_back((i+1)*(np+1)+j);

                  vecIndices.push_back(i*(np+1)+j);
                  vecIndices.push_back(i*(np+1)+(j+1));
                  vecIndices.push_back((i+1)*(np+1)+(j+1));
               }
               else
               {
                  vecIndices.push_back(i*(np+1)+j);
                  vecIndices.push_back((i+1)*(np+1)+j);
                  vecIndices.push_back((i+1)*(np+1)+(j-1));

                  vecIndices.push_back(i*(np+1)+j);
                  vecIndices.push_back(i*(np+1)+(j+1));
                  vecIndices.push_back((i+1)*(np+1)+j);
               }
            }
            else
            {

               vecIndices.push_back((i+1)*(np+1)-1);
               if (i<(2*np-1))
                  vecIndices.push_back((i+2)*(np+1)-2);
               else
                  vecIndices.push_back((i+2)*(np+1)-3);
               vecIndices.push_back((i+1)*(np+1)-2);
            }
         }
      }
   }
}
void Sphere::genTexture() // функия создания текстуры
{
   glGenTextures( 1, textureID);
    bool test = earthTexture.load(":/earth.jpg");
    if (test){glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);}
    earthTexture = QGLWidget::convertToGLFormat(earthTexture);
    glBindTexture(GL_TEXTURE_2D, textureID[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)earthTexture.width(), (GLsizei)earthTexture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, earthTexture.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}
