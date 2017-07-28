#ifndef SPHERE_H
#define SPHERE_H

#include <QVector>
#include <QtGui>
#include <math.h>

class Sphere
{
public:
    Sphere();

    void draw();

    const GLfloat pi=3.141593, k=pi/180;
    const GLuint np=36; // число частей, на которое делится полуокружность
    const GLfloat step=pi/np; // шаг изменения углов
private:
    void getVerTexArrays();
    void getIndexArray();
   // void genTexture();

    QVector<GLfloat> vecVertices; // вектор вершин
    QVector<GLfloat> vecTextures; // вектор текстурных координат
    QVector<GLuint> vecIndices; // вектор индексов вершин
};


#endif // SPHERE_H
