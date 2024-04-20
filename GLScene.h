#ifndef GLSCENE_H
#define GLSCENE_H

#include <common.h>
#include<GLParallax.h>
#include<GLPlayer.h>
#include<GLModel.h>
#include<GLInputs.h>
#include<GLTexture.h>
#include<GLEnms.h>
#include<GLTimer.h>
#include<GLCheckCollision.h>
#include<GLHealth.h>

class GLScene
{
    public:
        GLScene();
        virtual ~GLScene();
        GLint initGL();
        GLint drawScene();
        void drawGame(int);
        GLvoid resizeScene(GLsizei, GLsizei);
        void drawHealth(float);
        int windMsg(HWND,UINT,WPARAM,LPARAM);  // take windows inputs

        WPARAM wParam;                         // keyboard/Mouse msg

        float screenWidth;                     // get values from main window
        float screenHeight;                    // get Values from main window

        bool level1;
        bool level2;
        bool level3;
        bool level4;

        bool doneLoading;
        GLParallax *p = new GLParallax();
        GLPlayer *player = new GLPlayer();
        GLModel* m = new GLModel();
        GLTexture *mTex= new GLTexture();
        GLInputs *KbMs = new GLInputs();
        GLTexture* enmsTex = new GLTexture();
        GLTimer * timer = new GLTimer();
        GLHealth* health = new GLHealth();
        GLCheckCollision* hit = new GLCheckCollision();
        GLEnms E[20];
    protected:

    private:
};

#endif // GLSCENE_H
