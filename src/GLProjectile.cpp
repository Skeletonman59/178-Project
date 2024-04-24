#include "GLProjectile.h"

GLProjectile::GLProjectile()
{
    //ctor
    pScale.x =1.0; // default scaling
    pScale.y =1.0;

    pRotate.x =0;  // default rotations
    pRotate.y =0;
    pRotate.z =0;

    framesX =1;/*set later once we get it 1 is a place holder*/  // number of columns in the sprite sheet
    framesY =1;   // number of rows in the spritesheet

    xMax =1.0/framesX;  // default image
    xMin=0;
    yMax=1.0/framesY;
    yMin=0;

     myTime->startTime = clock();
}

GLProjectile::~GLProjectile()
{
    //dtor
}
void GLProjectile::drawProjectile()//we should pass a vec3 with the coordinate of the one passing; not sure how to do that yet
{
        glPushMatrix();
    glTranslatef(pos.x,pos.y,pos.z);
    glRotatef(pRotate.x,1,0,0);
    glRotatef(pRotate.y,0,1,0);
    glRotatef(pRotate.z,0,0,1);

    glScalef(pScale.x,pScale.y,1.0);

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

void GLProjectile::drawItem()
{
            glPushMatrix();
    glTranslatef(pos.x,pos.y,pos.z);
    glRotatef(pRotate.x,1,0,0);
    glRotatef(pRotate.y,0,1,0);
    glRotatef(pRotate.z,0,0,1);

    glScalef(pScale.x,pScale.y,1.0);

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

void GLProjectile::PlaceItem(vec3 p)
{
    pos.x =p.x;
    pos.y =p.y;
    pos.z =p.z;
}

void GLProjectile::ThrowProjectile(vec3 p,int direciton,int speed) // we could either use char here or the angle theta; not sure how to use theta just yet
{
    pos.x =p.x;
    pos.y =p.y;
    pos.z =p.z;

    switch(direction){

    case(RIGHT):
    pos.x+=(1*speed);
    break;
    case(LEFT):
    pos.x+=(1*speed);
    break;
    case(UP):
    pos.y+=(1*speed);
    break;
    case(DOWN):
    pos.y+=(1*speed);
    break;


    }

}

void GLProjectile::isExpire()
{
if(clock() - myTime->startTime>300)
{

    pScale.x =0.0; // scale it to 0 to remove it
    pScale.y =0.0;// only here because I'm not certain how to delete items


    myTime->startTime =clock();
}
}
