#include "GLParallax.h"

GLParallax::GLParallax()
{
    //ctor
    xMax=1.0;
    xMin=0.0;
    yMax =0.0;
    yMin = 1.0;

    alpha = 1;   //tune to 0 SLOWLY after newgame
    zPos = -2.0; // make 0 when newgame hit
}

GLParallax::~GLParallax()
{
    //dtor
}

void GLParallax::parallaxInit(char* fileName)
{

    background->loadTexture(fileName); //loading my background
    myTime->startTime = clock();
}

void GLParallax::parallaxScroll(bool Auto, string dir, float speed)
{
    if(Auto)
    {
        if(clock() - myTime->startTime>15)
        {

        if(dir=="up")
        {
           yMin -=speed;
           yMax -=speed;
        }
        if(dir=="down")
        {
           yMin +=speed;
           yMax +=speed;
        }
        if(dir=="left")
        {
           xMin -=speed;
           xMax -=speed;
        }
        if(dir=="right")
        {
           xMin +=speed;
           xMax +=speed;
        }

        myTime->startTime =clock();
        }
    }
}

void GLParallax::parallaxDraw(float width, float height)
{
    glColor3f(1.0,1.0,1.0); //white rectangle
    background->bindTexture();    //binding my background
    glBegin(GL_POLYGON);
        glTexCoord2f(xMin,yMin);
        glVertex3f(-width/height,-1,-8.0);

        glTexCoord2f(xMax,yMin);
        glVertex3f( width/height,-1,-8.0);

        glTexCoord2f(xMax,yMax);
        glVertex3f( width/height,1,-8.0);

        glTexCoord2f(xMin,yMax);
        glVertex3f(-width/height,1,-8.0);
    glEnd();

    //black overlay
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(0.0, 0.0, 0.0, alpha); // Black color with alpha
    glBegin(GL_QUADS);
      glVertex3f(-width/height, -1, -8.0);
      glVertex3f(width/height, -1, -8.0);
      glVertex3f(width/height, 1, -8.0);
      glVertex3f(-width/height, 1, -8.0);
    glEnd();

    glDisable(GL_BLEND);

}
