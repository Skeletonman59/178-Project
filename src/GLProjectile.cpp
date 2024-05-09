#include "GLProjectile.h"

GLProjectile::GLProjectile()
{
//con
}

GLProjectile::~GLProjectile()
{
    //dtor
}

void GLProjectile::drawProjectile()
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

void GLProjectile::PlaceItem(vec3 p) //places an item at any vec3 location
{
    pos.x =p.x;
    pos.y =p.y;
    pos.z =p.z;
}

void GLProjectile::ThrowProjectile(vec3 p,vec3 d,float speed) // general code for shooting; could work for both player and enemy
{

//pos.x =p.x;
 dest.y =p.y;
 dest.z =p.z;

if(clock() - myTime->startTime>30)
{

      pos.x = p.x +t*(d.x -p.x);
      pos.y = p.y +t*(d.y -p.y);
    //pos.z = p.z +t*(d.z -p.z);

     t<1? t+=0.05:t=0;

    /*
    switch(direction){

    case(1):
    pos.x += speed;
    break;
    case(2):
    pos.x += speed;
    break;
    case(3):
    pos.y += speed;
    break;
    case(4):
    pos.y += speed;
    break;

if (direction == 1) // left @ right
{
    pos.x += speed;
}
if (direction == 2)
{
    pos.x -= speed;
}
if (direction == 3)//up @ down
{
    pos.y += speed;
}
if (direction == 4)
{
    pos.y -= speed;
}*/
 if( pos.x == d.x && pos.y == d.y){
    isLive=false;
}
    myTime->startTime =clock();
    }


    if(clock() - anotherTime->startTime>30000)
    {
        isLive = false;
        anotherTime->startTime = clock();
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

void GLProjectile::initItem(vec3 plPos)
{
    pos = plPos;

    pScale.x = 0.2;
    pScale.y = 0.2;

    pRotate.x =0;
    pRotate.y =0;
    pRotate.z =90;

    xMin =0;
    yMin =0;
    xMax =1;
    yMax =1;

    isLive= false;
    myTime->startTime = clock();
    anotherTime->startTime = clock();

    dest.x =5.0; // use dest to shoot right
    dest.y =0;
    dest.z = 10;
    dest2.x =-5.0; // use dest2 to shoot left
    dest2.y =0;
    dest2.z = -4;
}

