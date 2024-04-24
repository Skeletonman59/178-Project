#ifndef GLSCENE_H
#define GLSCENE_H

#include <common.h>
#include<GLParallax.h>
#include<GLPlayer.h>
#include<GLLight.h>
#include<GLInputs.h>
#include<GLTexture.h>
#include<GLEnms.h>
#include<GLTimer.h>
#include<GLCheckCollision.h>
#include<GLSound.h>

class GLScene
{
    public:
        GLScene();
        virtual ~GLScene();
        GLint initGL();
        GLint drawScene();
        GLvoid resizeScene(GLsizei, GLsizei);
        float w, h;

        int windMsg(HWND,UINT,WPARAM,LPARAM);  // take windows inputs

        WPARAM wParam;                         // keyboard/Mouse msg

        float screenWidth;                     // get values from main window
        float screenHeight;                    // get Values from main window

        bool level1;
        bool level2;
        bool level3;
        bool level4;
        bool menuLoopTrigger;
        bool doneLoading;


GLInputs *kbMs = new GLInputs();    //keyboard and mouse
GLTimer *T = new GLTimer();
Screen *load = new Screen();         //static screen object
Screen *help = new Screen();         //much like a second parallax, this is a separate screen object
Screen *menu = new Screen();         //screen with button locations
Screen* pause = new Screen();
Screen *game = new Screen();
Screen *credit = new Screen();
Object *newgame = new Object();
Object *guide = new Object();
Object *quit = new Object();
GLPlayer* player = new GLPlayer();
GLParallax *p = new GLParallax();
GLSound *snds = new GLSound();

    protected:

    private:
};

#endif // GLSCENE_H
