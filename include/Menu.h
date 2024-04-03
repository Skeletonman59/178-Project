#ifndef MENU_H
#define MENU_H

#include<common.h>
#include<GLTexture.h>
#include<GLTimer.h>

//IN HINDSIGHT i probably didn't need a separate class, just two "Intro" objects
class Menu
{
public:
    Menu();
    virtual ~Menu();

    GLTexture *screen = new GLTexture();
    GLTimer   *myTime = new GLTimer();

    void menuInit(char *);       // load background file
    void menuDraw(float, float); // width and height
    void fadeIn(float);
    void appear(float);         //pushes the screen forward
    void setButtonGlow(bool);
    void drawButton(int, int, float, int, int);

    float xMax,xMin,yMax,yMin,zPos, xPos;
    float alphaIter, alpha;

    int BUTTON_LEFT_LIMIT;   //why no differing xVal? all buttons will be the same width
    int BUTTON_RIGHT_LIMIT;
    int NEW_GAME_Y1;
    int NEW_GAME_Y2;
    int HELP_Y1;
    int HELP_Y2;
    int QUIT_Y1;
    int QUIT_Y2;

    enum {NONE, NEW, HELP, QUIT}; //stages in which either the cursor or the arrow keys will change.
    int buttonToggle; //for enum changes
protected:

private:
};

#endif // MENU_H
