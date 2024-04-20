#ifndef GLHEALTH_H
#define GLHEALTH_H
#include<common.h>
#include<GLTimer.h>
#include<GLTexture.h>

class GLHealth
{
    public:
        GLHealth();
        virtual ~GLHealth();
        void initHealth(int,int,char*);
        void drawHealth();
        void status();
        GLTexture* texture = new GLTexture();
        vec3 plPosition;
        vec3 plScale;
        GLTimer   *myTime = new GLTimer();
        vec3 vert[4];
        float xMax,xMin,yMax,yMin;
        int framesX,framesY;

        int statusTrigger;  // for load actions


    protected:

    private:
};

#endif // GLHEALTH_H
