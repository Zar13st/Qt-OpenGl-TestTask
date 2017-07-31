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

    const GLuint np = 36; // число частей, на которое делится полуокружность
    const GLfloat step = M_PI / np; // шаг изменения углов
private:
    void getVerTexArrays();
    void getIndexArray();
    //void genTexture();

    QVector<GLfloat> vecVertices; // вектор вершин
    QVector<GLfloat> vecTextures; // вектор текстурных координат
    QVector<GLuint> vecIndices; // вектор индексов вершин

    GLuint textureID;
};


#endif // SPHERE_H
