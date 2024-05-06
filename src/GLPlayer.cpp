#include "GLPlayer.h"

GLPlayer::GLPlayer()
{
    //ctor

    vert[0].x =-0.5; vert[0].y = -0.5; vert[0].z =-1.0;
    vert[1].x = 0.5; vert[1].y = -0.5; vert[1].z =-1.0;
    vert[2].x = 0.5; vert[2].y =  0.5; vert[2].z =-1.0;
    vert[3].x =-0.5; vert[3].y =  0.5; vert[3].z =-1.0;

}

GLPlayer::~GLPlayer()
{
    //dtor
}
bool GLPlayer::leftBound()        //check if player is hitting left wall
{
    return plPosition.x <= -1.35;

}
bool GLPlayer::rightBound()        // check if player is hitting right wall
{
    return plPosition.x >= 1.35;
}


void GLPlayer::initPlayer(int x, int y, char* fileName)
{
    plPosition.x =-1.3;         // initialize positions
    plPosition.y =-0.475;
    plPosition.z = -5.0;

   plScale.x = 0.3;           // initialize scale
    plScale.y = 0.3;
    plScale.z = 1.0;

    framesX = x;               // record number of frames
    framesY = y;

    texture->loadTexture(fileName); //loading my background

    xMin =0;
    yMax =2.0/(float)framesY;
    xMax =1.0/(float)framesX;
    yMin =yMax-1.0/(float)framesY;

    actionTrigger=0;
    t = 0;
    vY = 20;
    myTime->startTime = clock();
}

void GLPlayer::drawPlayer()
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

void GLPlayer::actions()
{
if((clock() - myTime->startTime) > 100){

   switch(actionTrigger)
   {
   case STAND:

       xMin =0;
       xMax = 1.0/(float)framesX;

       yMax =1.0/(float)framesY;
       yMin =yMax-1.0/(float)framesY;

       break;

   case WALKLEFT:                   // position moving left & if left wall-> stop
  if( leftBound()){
        actionTrigger = STAND;
       }
       else{
		//plScale.x = -0.3f;
       yMax =2.0/(float)framesY;
       yMin =yMax-1.0/(float)framesY;

       xMax += 1.0/(float)framesX;
       xMin += 1.0/(float)framesX;
       plPosition.x -=.06;
   }
       break;

   case WALKRIGHT:                 //position moving right & if right wall -> stop
    if( rightBound()){
        actionTrigger = STAND;
       }
       else{
		plScale.x = 0.3f;
        yMax=3.0/(float)framesY;
        yMin=yMax-1.0/(float)framesY;

        xMin+=1.0/(float)framesX;
        xMax+=1.0/(float)framesX;
        plPosition.x +=.06;

       }
       break;

   case JUMP:
	   jumping = true;
	break;

   default: break;
   }
   if(jumping)
   {
	   plPosition.y += (vY * t - 0.5 * GRAVITY * pow(t,2)) / 300;
       t += 0.4f;
       if(plPosition.y < -0.475f) {t = 0; actionTrigger = STAND; plPosition.y = -0.475f; jumping = false;}
   }
   myTime->startTime = clock();


   }
}
