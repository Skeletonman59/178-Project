#include "GLHealth.h"

GLHealth::GLHealth()
{
      vert[0].x =-0.5; vert[0].y = -0.5; vert[0].z =-1.0;
    vert[1].x = 0.5; vert[1].y = -0.5; vert[1].z =-1.0;
    vert[2].x = 0.5; vert[2].y =  0.5; vert[2].z =-1.0;
    vert[3].x =-0.5; vert[3].y =  0.5; vert[3].z =-1.0;

}

GLHealth::~GLHealth()
{
    //dtor
}
void GLHealth::initHealth(int x, int y, char* fileName)
{
    plPosition.x =-0.41;         // initialize positions
    plPosition.y =0.2;
    plPosition.z = -1.0;

    plScale.x = 0.05;           // initialize scale
    plScale.y = 0.05;
    plScale.z = 1.0;

    framesX = x;               // record number of frames
    framesY = y;

    texture->loadTexture(fileName); //loading my background

    xMin =0;
    yMax =1.0/(float)framesY;
    xMax =1.0/(float)framesX;
    yMin =yMax-1.0/(float)framesY;

       // statusTrigger=0;
        myTime->startTime = clock();


}

void GLHealth::drawHealth()
{

    glTranslatef(plPosition.x,plPosition.y,plPosition.z);
    glScalef(plScale.x,plScale.y,plScale.z);

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

void GLHealth::status()
{if((clock() - myTime->startTime) > 30){

    switch(statusTrigger)
    {
    case 0:                               // As case goes down -> health goes down

    xMax =1.0/framesX;  // default image
    xMin=0;

    yMax=1.0/framesY;
    yMin=0;
    break;


    case 1:
        yMax=2.0/(float)framesY;
        yMin= yMax-1.0/(float)framesY;
        xMin=0;
        xMax=1.0/(float)framesX;
        break;

    case 2:
        yMax=3.0/(float)framesY;
        yMin= yMax-1.0/(float)framesY;
        xMin=0;
        xMax=1.0/(float)framesX;
        break;

    case 3:
        yMax=4.0/(float)framesY;
        yMin= yMax-1.0/(float)framesY;
        xMin=0;
        xMax=1.0/(float)framesX;
        break;

    case 4:
        yMax=5.0/(float)framesY;
        yMin= yMax-1.0/(float)framesY;
        xMin=0;
        xMax=1.0/(float)framesX;
        break;

    case 5:
        yMax=6.0/(float)framesY;
        yMin= yMax-1.0/(float)framesY;
        xMin=0;
        xMax=1.0/(float)framesX;
        break;



    }
      myTime->startTime = clock();


   }
}
