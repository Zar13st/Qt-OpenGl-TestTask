#include "satellite.h"

Satellite::Satellite()
{
    getVerArrays();
}

Satellite::~Satellite()
{

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

void Satellite::setAlfa(GLfloat alfa)
{
    this->alfa = alfa;
}

void Satellite::setBeta(GLfloat beta)
{
    this->beta = beta;
}

void Satellite::setR(GLfloat R)
{
    this->R = R;
}

void Satellite::setSpeed(GLfloat speed)
{
    this->speed = speed;
}

void Satellite::getVerArrays()
{
    vecVertices.clear();

    GLfloat X,Y,Z;
    GLfloat XafterOXrot, YafterOXrot, ZafterOXrot;
    GLfloat XafterOYrot, YafterOYrot, ZafterOYrot;
    //стартовая позиция спутника
    X = R*sin(phi);
    Y = R*cos(phi);
    Z = 0;
    //позиция спутника после поворота вокруг ОХ, используем матрицу поворота
    XafterOXrot = 1 * X + 0 * Y + 0 * Z;
    YafterOXrot = 0 * X + cos(alfa) * Y + -sin(alfa) * Z;
    ZafterOXrot = 0 * X + sin(alfa) * Y + cos(alfa) * Z;
    //позиция спутника после поворота вокруг ОY, используем матрицу поворота
    XafterOYrot = cos(beta) * XafterOXrot + 0 * YafterOXrot + sin(beta) * ZafterOXrot;
    YafterOYrot = 0 * XafterOXrot + 1 * YafterOXrot + 0 * ZafterOXrot;
    ZafterOYrot = -sin(beta) * XafterOXrot + 0 * YafterOXrot + cos(beta) * ZafterOXrot;

    vecVertices.push_back(XafterOYrot);
    vecVertices.push_back(YafterOYrot);
    vecVertices.push_back(ZafterOYrot);
}
