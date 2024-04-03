#include "Menu.h"

Menu::Menu()
{
    //ctor
    xMax=1.0;
    xMin=0.0;
    yMax =0.0;
    yMin = 1.0;

    zPos = -1;
    xPos = 0;  //for screen
    alpha = 1.0;

    //each box is 230 wide, 80 high

    BUTTON_LEFT_LIMIT = 545;
    BUTTON_RIGHT_LIMIT = 775;
    NEW_GAME_Y1 = 360;
    NEW_GAME_Y2 = 440;
    HELP_Y1 = 450;
    HELP_Y2 = 530;
    QUIT_Y1 = 550;
    QUIT_Y2 = 630;

    buttonToggle = NONE;
}

Menu::~Menu()
{
    //dtor
}

void Menu::menuInit(char* filename)
{
    screen->loadTexture(filename);
    myTime->startTime = clock();
}

void Menu::menuDraw(float width, float height)
{
    glColor4f(1.0,1.0,1.0, alpha); //white rectangle
    screen->bindTexture();    //binding my background
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

