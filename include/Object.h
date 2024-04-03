#ifndef OBJECT_H
#define OBJECT_H

#include<common.h>
#include<GLTexture.h>
#include<GLTimer.h>

//We treat the object like a player, for easier background fixes
class Object
{
    public:
        Object();
        virtual ~Object();

        GLTexture *texture = new GLTexture();
        GLTimer   *myTime = new GLTimer();

        void initObject(int,int,char* fileName); // number of x, y frames, MOST LIKELY AT TOP OF FILE
        void drawObject();
        void objectMove(float, float);

        vec3 objPosition;
        vec3 objScale;

        vec3 vert[4];
        float xMax,xMin,yMax,yMin;
        int framesX,framesY;
        bool pause;
        bool ret;

        //int actionTrigger;  // for load actions

    protected:

    private:
};

#endif // OBJECT_H
