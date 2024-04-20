#ifndef GLENMS_H
#define GLENMS_H

#include<common.h>
#include<GLTexture.h>
#include<GLTimer.h>

class GLEnms
{
    public:
        GLEnms();
        virtual ~GLEnms();

        void drawEnemy();
        void PlaceEnemy(vec3);
        void setFrames(int,int);
        void actions();
        bool rightBound();
        bool leftBound();


        bool isEnemyLive =true;

        vec3 pos;
        vec2 eScale;
        vec3 eRotate;

        int framesX;
        int framesY;

        int action;
        float speed;
        float xMax,xMin,yMax,yMin;
        GLTexture * texture = new GLTexture();
        GLTimer   *myTime = new GLTimer();

    protected:

    private:
};

#endif // GLENMS_H
