#ifndef GLSCENE_H
#define GLSCENE_H

#include <common.h>
#include <GLTimer.h>
#include<GLScene.h>
#include<GLLight.h>
#include<GLParallax.h>
#include<GLTexture.h>
#include<GLInputs.h>
#include<Screen.h>
#include<Object.h>
#include <GLPlayer.h>
#include <GLEnms.h>
#include <GLCheckCollision.h>
#include<GLSounds.h>
#include<GLProjectile.h>


class GLScene
{
public:
    GLScene();
    virtual ~GLScene();

    GLInputs *kbMs = new GLInputs();    //keyboard and mouse
    GLTimer *T = new GLTimer();
    Screen *load = new Screen();         //static screen object
    Screen *help = new Screen();         //much like a second parallax, this is a separate screen object
    Screen *menu = new Screen();         //screen with button locations
    Screen *pause = new Screen();
    Screen *game = new Screen();
    Screen *credit = new Screen();

    Object *newgame = new Object();
    Object *guide = new Object();
    Object *quit = new Object();
    GLParallax *p = new GLParallax();

    GLSounds *snds = new GLSounds();

    GLPlayer *player = new GLPlayer();
    GLEnms E[20];
    GLProjectile P[6];
    GLProjectile coin[100];
    GLTexture enmTexture[3];
    GLTexture *BulletTex = new GLTexture();
    GLTexture *CoinTex = new GLTexture();
    GLCheckCollision *hit = new GLCheckCollision();
    GLTimer* Iframe = new GLTimer();

    Object* health = new Object();
    Object* bullet = new Object();

    float enmT;
    float enmSpawnRate;
    int enmN;
    int maxEnms;

    GLint initGL();
    GLint drawScene();
    GLvoid resizeScene(GLsizei, GLsizei);
    float w, h;
    int Ammo=6;
    int Gold=0;
    int coinIter=0;
    int goal = 3;

    int windMsg(HWND,UINT,WPARAM,LPARAM);  // take windows inputs

    WPARAM wParam;                         // keyboard/Mouse msg

    float screenWidth;                     // get values from main window
    float screenHeight;                    // get Values from main window

    bool level1;
    bool level2;
    bool level3;
    bool level4;
    bool doneLoading;
    vec3 deleted;

    int sndsIterator;


protected:

private:
};

#endif // GLSCENE_H
