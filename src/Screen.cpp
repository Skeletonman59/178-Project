#include "Screen.h"

Screen::Screen()
{
    //ctor
    xMax=1.0;
    xMin=0.0;
    yMax =0.0;
    yMin = 1.0;

    screenTrigger = 0;
    menuLock = false;
}

Screen::~Screen()
{
    //dtor
}
void Screen::screenInit(float x, float y, float z, float a, char* filename)
{
    xPos = x;
    yPos = y;
    zPos = z;
    alpha = a;
    bg->loadTexture(filename); //loading my background
    myTime->startTime = clock();
}

void Screen::screenDraw(float width, float height)
{
    glColor3f(1.0,1.0,1.0); //white rectangle
    bg->bindTexture();      //binding my background
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

void Screen::actions()
{
    switch(screenTrigger)
    {
    case NOTHING:
        break;
    case FADEIN:
        zPos = 0;  //bring screen forward
        if(clock() - myTime->startTime>30)
        {
            if (alpha > 0.01)
            {
                alpha-=0.1;
            }
            myTime->startTime =clock();
        }
        break;
    case FADEOUT:
        if(clock() - myTime->startTime>30)
        {
            if  (alpha < 1.0) alpha+=0.1;
            else
            {
                zPos = -1; //push screen back
                //menuLock = false;
            }
            myTime->startTime =clock();
        }
        break;
    case HELPIN:
        if(clock() - myTime->startTime>10)
        {
            if(xPos < 0) xPos+=0.1;
            else xPos = 0;
            //kbMs->helpTransitioning = false; // Reset transitioning flag
            myTime->startTime =clock();
        }
        break;
    case HELPOUT:
        if(clock() - myTime->startTime>10)
        {
            if(xPos > -4) xPos-=0.1;
            //kbMs->helpTransitioning = false; // Reset transitioning flag
            myTime->startTime =clock();
        }
        break;
    }
}
