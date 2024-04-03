#include "Object.h"

Object::Object()
{
    //ctor
    vert[0].x =-0.5; vert[0].y = -0.5; vert[0].z =-1.0;
    vert[1].x = 0.5; vert[1].y = -0.5; vert[1].z =-1.0;
    vert[2].x = 0.5; vert[2].y =  0.5; vert[2].z =-1.0;
    vert[3].x =-0.5; vert[3].y =  0.5; vert[3].z =-1.0;
}

Object::~Object()
{
    //dtor
}
void Object::initObject(int x, int y, char* fileName)
{
    objPosition.x = -0.55;  //initialize position
    objPosition.y = 1.5;    //out of screen until needed
    objPosition.z = -1.0;

    objScale.x = 0.5;  //initialize scale
    objScale.y = 0.5;
    objScale.z = 1.0;

    framesX = x;               // record number of frames
    framesY = y;

    texture->loadTexture(fileName); //loading my background

    xMin = 0;
    xMax = 1.0/(float)framesX;
    yMax = 2.0/(float)framesY;
    yMin = yMax-2.0/(float)framesY;

    pause = false;
    ret = false;


    myTime->startTime = clock();
}

void Object::drawObject()
{
    glTranslatef(objPosition.x,objPosition.y,objPosition.z);
    glScalef(objScale.x,objScale.y,objScale.z);

    glColor3f(1.0,1.0,1.0);    //white rectangle
    texture->bindTexture();    //binding my background


    glBegin(GL_QUADS);
      glTexCoord2f(xMin,yMax);
      glVertex3f(vert[0].x,vert[0].y,vert[0].z);

      glTexCoord2f(xMax,yMax);
      glVertex3f(vert[1].x,vert[1].y,vert[1].z);

      glTexCoord2f(xMax,yMin);
      glVertex3f(vert[2].x,vert[2].y,vert[2].z);

      glTexCoord2f(xMin,yMin);
      glVertex3f(vert[3].x,vert[3].y,vert[3].z);

    glEnd();
}
void Object::objectMove(float y,float x)
{
    if(!pause)
    {
        objPosition.y = y;
        objPosition.x = x;
        pause = true;
    }
    if((clock() - myTime->startTime) > 45)
    {
        if(!ret) objPosition.y +=0.1;
        else objPosition.y -=0.1;
        if(objPosition.y >= -0.15) ret = true;
        if(objPosition.y <= y)
        {
            ret = false;
            pause = false;
        }
        myTime->startTime = clock();
    }
}
