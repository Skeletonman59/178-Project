#ifndef SCREEN_H
#define SCREEN_H

#include<common.h>
#include<GLTexture.h>
#include<GLTimer.h>

class Screen
{
    public:
        Screen();

        GLTexture *bg = new GLTexture();
        GLTimer   *myTime = new GLTimer();
        virtual ~Screen();

        void screenInit(float, float, float, float, char*);        // load background file
        void screenDraw(float, float);  // width and height
        float xMax,xMin,yMax,yMin,zPos,xPos, yPos;
        float alphaIter, alpha;

        enum{NOTHING, FADEIN, FADEOUT, HELPIN, HELPOUT, ON, OFF, POPTOMIDDLE, POPFROMMIDDLE};
        bool lScreen;

        void actions();
        int screenTrigger;
        bool current;
        bool menuLock;  //prevents all actions from being done at once.

    protected:

    private:
};

#endif // SCREEN_H
