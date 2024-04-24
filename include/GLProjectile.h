#ifndef GLPROJECTILE_H
#define GLPROJECTILE_H

#include<common.h>
#include<GLTexture.h>
#include<GLTimer.h>
#include<GLCheckCollision.h>

class GLProjectile
{
    public:
        GLProjectile();
        virtual ~GLProjectile();

        void drawProjectile();
        void drawItem();
        void PlaceItem(vec3);// basically for the enemies to drop coins or add health packs or something
        void ThrowProjectile(vec3,int,int);// vec3 for when the projectile is fired; char for the direction that it will speed towards
        void isExpire();//for the projectile to expire after some time

        vec3 pos;
        vec2 pScale;
        vec3 pRotate;

        int framesX;
        int framesY;

        float speed;
        float xMax,xMin,yMax,yMin;
        GLTimer   *myTime = new GLTimer();

        float t; // projectile timer
        float theta;// angle of projectile
        int direction; // select movement direction

        enum {LEFT,RIGHT,UP,DOWN};

    protected:

    private:
};

#endif // GLPROJECTILE_H
