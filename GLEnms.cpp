#include "GLEnms.h"

GLEnms::GLEnms()
{
    pos.x =0;    // Default position settings
    pos.y =0;
    pos.z =-2;

    eScale.x =1.0; // default scaling
    eScale.y =1.0;

    eRotate.x =0;  // default rotations
    eRotate.y =0;
    eRotate.z =0;

    framesX =4;   // number of columns in the sprite sheet
    framesY =4;   // number of rows in the sprite sheet

    xMax =1.0/(float)framesX;  // default image
    xMin=0;

    yMax=1.0/(float)framesY;
    yMin =yMax-1.0/(float)framesY;

    speed =0.01;  // moving speed
    action=2;     // set actions
    myTime->startTime = clock();

}

GLEnms::~GLEnms()
{
    //dtor

}
void GLEnms::setFrames(int x,int y)
{
    framesX=x;
    framesY=y;


}
bool GLEnms::rightBound(){      //check if enemy is hitting right wall
  return pos.x >= 1.35;

}
bool GLEnms::leftBound(){       //check if enemy is hitting left wall
  return pos.x <= -1.35;

}

void GLEnms::drawEnemy()
{
    glPushMatrix();
    glTranslatef(pos.x,pos.y,pos.z);
    glRotatef(eRotate.x,1,0,0);
    glRotatef(eRotate.y,0,1,0);
    glRotatef(eRotate.z,0,0,1);

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

void GLEnms::PlaceEnemy(vec3 p)
{
    pos.x =p.x;
    pos.y =p.y;
    pos.z =p.z;
}

void GLEnms::actions()
{
    switch(action)
    {
    case 0:
        if(clock() - myTime->startTime>60){


        yMax=4.0/ (float)framesY;
        yMin= yMax -1.0 / (float)framesY;
        xMin +=1.0/framesX;
        xMax +=1.0/framesX;

         pos.x +=speed;


        myTime->startTime =clock();
        }
        break;

    case 1:
        if(clock() - myTime->startTime>60){



        yMax=2.0 / (float)framesY;
        yMin= yMax-1.0 / (float)framesY;
        xMin +=1.0/framesX;
        xMax +=1.0/framesX;
        pos.x +=speed;
         myTime->startTime =clock();
        }
        break;
    case 2:
if(clock() - myTime->startTime>60){
        yMax= 4.0 / (float)framesY;
        yMin= yMax-1.0 / (float)framesY;
        xMin +=1.0/framesX;
        xMax +=1.0/framesX;
        pos.y -=speed;
         myTime->startTime =clock();
}

        break;

    case 3:

    xMax =1.0/framesX;  // default image
    xMin=0;

    yMax=1.0/framesY;
    yMin=0;
        break;
    case 4:

        yMax=4.0 / (float)framesY;
        yMin= yMax-1.0 / (float)framesY;
        xMin +=1.0/framesX;
        xMax +=1.0/framesX;
        pos.y +=.05;


break;
    case 5:
if(clock() - myTime->startTime>60){          //bounce left and up
        yMax= 4.0 / (float)framesY;
        yMin= yMax-1.0 / (float)framesY;
        xMin +=1.0/framesX;
        xMax +=1.0/framesX;
        pos.y +=speed;
        pos.x-=speed;
         myTime->startTime =clock();
}

        break;
   case 6:
        if(clock() - myTime->startTime>60){    // bounce right and up

        yMax=4.0 / (float)framesY;
        yMin= yMax-1.0 / (float)framesY;
        xMin +=1.0/framesX;
        xMax +=1.0/framesX;
        pos.y +=speed;
        pos.x+= speed;
        myTime->startTime =clock();
}

        break;

        case 7:
if(clock() - myTime->startTime>60){        // bounce left and go down
        yMax= 4.0 / (float)framesY;
        yMin= yMax-1.0 / (float)framesY;
        xMin +=1.0/framesX;
        xMax +=1.0/framesX;
        pos.y -=speed;
        pos.x-=speed;
         myTime->startTime =clock();
}

        break;
   case 8:
        if(clock() - myTime->startTime>60){     //bounce right and go down

        yMax=4.0 / (float)framesY;
        yMin= yMax-1.0 / (float)framesY;
        xMin +=1.0/framesX;
        xMax +=1.0/framesX;
        pos.y -=speed;
        pos.x+= speed;
        myTime->startTime =clock();
}

        break;
    }

}
