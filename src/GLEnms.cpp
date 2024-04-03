#include "GLEnms.h"

GLEnms::GLEnms()
{
    //ctor
    //TODO: EVERYTHING IN THIS FILE IS TO BE CHANGED ACCORDING TO GAME DESIGN
/*
    pos.x =0;    // Default position settings
    pos.y =0;
    pos.z =-2;

    eScale.x =1.0; // default scaling
    eScale.y =1.0;

    xMax =1.0;  // default image
    xMin=0;
    yMax=1.0;
    yMin=0;

    speed =0.01;  // moving speed
    myTime->startTime = clock();
    */
}

GLEnms::~GLEnms()
{
    //dtor

}
void GLEnms::enemyInit(char* fileName)
{
    /*
    pos.x = 0.0;  //initialize position
    pos.y = -0.45;
    pos.z = -1.0;

    eScale.x = 0.5;  //initialize scale
    eScale.y = 0.5;
    eScale.z = 1.0;

    texture->loadTexture(fileName);

    myTime->startTime = clock();
    */
}


void GLEnms::drawEnemy()
{
    glPushMatrix();
    glTranslatef(pos.x,pos.y,pos.z);

    glScalef(eScale.x,eScale.y,1.0);

     glBegin(GL_QUADS);
      glTexCoord2f(xMin,yMax);
      glVertex3f(-1,-1,0);

      glTexCoord2f(xMax,yMax);
      glVertex3f(1,-1,0);

      glTexCoord2f(xMax,yMin);
      glVertex3f(1,1,0);

      glTexCoord2f(xMin,yMin);
      glVertex3f(-1,1,0);

   glEnd();
   glPopMatrix();

}
