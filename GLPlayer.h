#ifndef GLPLAYER_H
#define GLPLAYER_H

#include<common.h>
#include<GLTexture.h>
#include<GLTimer.h>

class GLPlayer
{
    public:
        GLPlayer();
        virtual ~GLPlayer();

        enum {STAND, WALKLEFT,WALKRIGHT, RUN, JUMP, ATTACK};

        GLTexture *texture = new GLTexture();
        GLTimer   *myTime = new GLTimer();

        void initPlayer(int,int,char* fileName); // number of x, y frames
        void drawPlayer();
        void actions();
        bool leftBound();
        bool rightBound();

        vec3 plPosition;
        vec3 plScale;

        vec3 vert[4];
        float xMax,xMin,yMax,yMin;
        int framesX,framesY;
        float screenWidth;                     // get values from main window
        float screenHeight;
        int actionTrigger;  // for load actions
        float currHealth =5;
        int maxHealth =5;

    protected:

    private:
};

#endif // GLPLAYER_H
