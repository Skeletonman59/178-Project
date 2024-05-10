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
        void actions();

        bool isEnemyLive =true;
        int enemyHealth = 4;

        enum{STAND,WALKLEFT,WALKRIGHT,ROLLLEFT,ROLLRIGHT,ATTACK};

        vec3 pos;
        vec2 eScale;
        vec3 eRotate;

        int framesX;
        int framesY;

        int action;
        float speed;
        float xMax,xMin,yMax,yMin;
        GLTimer   *myTime = new GLTimer();

        int v;   // velocity
        float t; // projectile timer
        float theta;// angle of projectile
        float radius=0.2;

        float spawnTimer;	// Timer for spawns
        GLTexture *tex = new GLTexture();


    protected:

    private:
};

#endif // GLENMS_H
