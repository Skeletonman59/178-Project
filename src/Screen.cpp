#include "Screen.h"

Screen::Screen()
{
    //ctor
    xMax=1.0;
    xMin=0.0;
    yMax =0.0;
    yMin = 1.0;

    zPos = 0;
    xPos = 0;  //for help
    alpha = 0;
}

Screen::~Screen()
{
    //dtor
}
void Screen::screenInit(char* filename)
{
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




