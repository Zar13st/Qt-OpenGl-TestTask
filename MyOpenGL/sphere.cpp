#include "sphere.h"

Sphere::Sphere()
{
    getVerTexArrays();
    getIndexArray();
    //genTexture();
}

void Sphere::draw()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
    glVertexPointer(3, GL_FLOAT, 0, vecVertices.begin());
    // указываем, откуда нужно извлечь данные о массиве текстурных координат
    //glTexCoordPointer(2, GL_FLOAT, 0, vecTextures.begin());
    // строим поверхности
    glDrawElements(GL_TRIANGLES, vecIndices.size(), GL_UNSIGNED_INT, vecIndices.begin());
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
               vecVertices.push_back(0.0f); // пространственная x-координата вершины
               vecVertices.push_back(R);    // пространственная y-координата вершины
               vecVertices.push_back(0.0f); // пространственная z-координата вершины

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
                  vecVertices.push_back(R*cos(theta));
                  vecVertices.push_back(R*sin(theta)*sin(phi));

                  vecTextures.push_back(phi/(2*M_PI));
               }
               else
               {
                  vecVertices.push_back(R*sin(theta));
                  vecVertices.push_back(R*cos(theta));
                  vecVertices.push_back(0.0f);

                  vecTextures.push_back(1.0f);
               }
               vecTextures.push_back((M_PI-theta)/M_PI);
            }
            else // вершины "южный полюс"
            {
               if (i<2*np)
               {
                  vecVertices.push_back(0.0f);
                  vecVertices.push_back(-R);
                  vecVertices.push_back(0.0f);

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
/*void Sphere::genTexture() // функия создания текстуры
{
   // создаём, связываем, загружаем, возвращаем уникальный номер:
   textureID[0]=bindTexture(QPixmap(QString("earth.jpg")), GL_TEXTURE_2D, GL_RGBA);
   // далее параметры текстурного объекта
   // при фильтрации игнорируются тексели, выходящие за границу текстуры для s координаты
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   // при фильтрации игнорируются тексели, выходящие за границу текстуры для t координаты
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   // цвет текселя полностью замещает цвет фрагмента фигуры
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}*/
