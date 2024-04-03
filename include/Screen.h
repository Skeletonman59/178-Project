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

        void screenInit(char *);// load background file
        void screenDraw(float, float); // width and height
        void blackFade(float);          //fades "screen" to black
        void retreat(float);            //makes the loading screen move back, or return if inverted values

        float xMax,xMin,yMax,yMin,zPos, xPos;
        float alphaIter, alpha;

    protected:

    private:
};

#endif // SCREEN_H
