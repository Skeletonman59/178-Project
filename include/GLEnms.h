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

        GLTexture *texture = new GLTexture();
        GLTimer   *myTime = new GLTimer();

        void enemyInit(char*);
        void drawEnemy();
        void PlaceEnemy(vec3);

        vec3 pos; //random x, below screen y, gamescreen z
        vec3 eScale;

        int action;
        float speed;
        float xMax,xMin,yMax,yMin;

    protected:

    private:
};

#endif // GLENMS_H
