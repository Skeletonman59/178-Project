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

        void initObject(float, float, float, int,int,char* fileName); // number of x, y frames, MOST LIKELY AT TOP OF FILE
        void drawObject();

        void new_button(float, float, float, float);
        void guide_button(float, float, float, float);
        void quit_button(float, float, float, float);

        vec3 objPosition;
        vec3 objScale;

        vec3 vert[4];
        float xMax,xMin,yMax,yMin;
        int framesX,framesY;

        //left limit is 0, buttons are stuck on the left.
        float BUTTON_RIGHT_LIMIT;
        float BUTTON_TOP_LIMIT;
        float BUTTON_BOTTOM_LIMIT;

        float normalizedBRL;
        float normalizedBTL;
        float normalizedBBL;

        void actions();
        int moveTrigger;
        enum{APPEAR, POP, RETREAT, DISAPPEAR};


    protected:

    private:
};

#endif // OBJECT_H
