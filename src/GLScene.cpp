#include<GLScene.h>
#include<GLLight.h>
#include<GLParallax.h>
#include<GLTexture.h>
#include<GLInputs.h>
#include<GLTimer.h>
#include<Screen.h>
#include<Object.h>
#include <GLPlayer.h>
#include <GLEnms.h>
#include <GLCheckCollision.h>
#include<GLSounds.h>

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
GLCheckCollision *hit = new GLCheckCollision();


GLScene::GLScene()
{
    //ctor

    screenWidth  = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    level1=  true;   //Used to switch through screens
    level2= false;
    level3=false;
    level4=false;
    sndsIterator = 0;
    doneLoading= false;

}

GLScene::~GLScene()
{
    //dtor
}

GLint GLScene::initGL()
{
    glShadeModel(GL_SMOOTH); // for smooth render
    glClearColor(0.0f,0.0f,0.0f,0.0f); // clear background to black
    glClearDepth(2.0f);            // depth test for layers
    glEnable(GL_DEPTH_TEST);       // activate depth test
    glDepthFunc(GL_LEQUAL);         // depth function type

    GLLight Light(GL_LIGHT0);
    Light.setLight(GL_LIGHT0);

    glEnable(GL_BLEND);             // Transparent effect of pngs
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);  //enable textures
    load->screenInit( 0, 0,  0, 0, "images/menu/loadmenu.png");
    menu->screenInit( 0, 0, -1, 1, "images/menu/2.png");
    help->screenInit(-4, 0, 0.01, 0, "images/menu/helpmenu.png"); //seriously, who's gonna tell the help menu is 0.01 units closer?
    pause->screenInit(0, 0, 0, 0, "images/menu/pause.png");
    credit->screenInit(0,0,0,0,"images/menu/creators.png");
    load->current = true;

    //                x  y   z  a

    newgame->initObject(-2,0.11,0,2,5, "images/menu/buttons.png");
    //newgame->new_button(w,h, screenWidth, screenHeight);
    guide->initObject(-2,-0.08,0,2,5, "images/menu/buttons.png");
    guide->guide_button(w,h, screenWidth, screenHeight);
    quit->initObject(-2,-0.27,0,2,5, "images/menu/buttons.png");
    quit->quit_button(w,h, screenWidth, screenHeight);

    snds->initSounds();
    snds->myTime->startTime = clock();

    T->startTime = clock();

    player->initPlayer(4,4,"images/game/poke.png");
    for(int i=0; i<20; i++)
    {
        E[i].pos.x = (float)rand()/(float)RAND_MAX*5-2.5;
        E[i].pos.y =-1.2;
        E[i].pos.x<player->plPosition.x?E[i].action =E[i].WALKRIGHT:E[i].action =E[i].WALKLEFT;
        E[i].eScale.x = E[i].eScale.y = (float)(rand()%12)/30.0;
    }
    if(level1)
    {
        p->parallaxInit("images/game/stage1.png");
        doneLoading=true;

    }
    if(level2)
    {
        p->parallaxInit("images/game/stage2.png");
        doneLoading=true;
    }
    if(level3)
    {
        p->parallaxInit("images/game/stage3.png");
        doneLoading=true;
    }
    if(level4)
    {
        p->parallaxInit("images/game/stage4.png");
        doneLoading=true;
    }


    return true;
}

GLint GLScene::drawScene()    // this function runs on a loop
// DO NOT ABUSE ME
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);// clear bits in each iteration
    glLoadIdentity();
    glColor3f(1.0,1.0,1.0);     //color the object red

    if(load->current)
    {
        glPushMatrix();     //group object
        glScalef(3.33,3.33,1.0);
        glDisable(GL_LIGHTING);
        glTranslatef(load->xPos, load->yPos, load->zPos);
        load->screenDraw(screenWidth, screenHeight);  //draw model obj
        load->actions();
        glEnable(GL_LIGHTING);
        glPopMatrix();

        snds->playMenu();
    }
    if(menu->current)
    {
        newgame->new_button(w,h, screenWidth, screenHeight);
        glPushMatrix();
        glScalef(3.33,3.33,1.0);
        glDisable(GL_LIGHTING);
        glTranslatef(menu->xPos, menu->yPos, menu->zPos);
        menu->screenDraw(screenWidth, screenHeight);
        menu->actions();
        glEnable(GL_LIGHTING);
        glPopMatrix();

        snds->stopGameSound();
        snds->playMenu();
    }

    if(credit->current)
    {
        glPushMatrix();
        glScalef(3.33,3.33,1.0);
        glDisable(GL_LIGHTING);
        glTranslatef(credit->xPos, credit->yPos, credit->zPos);
        credit->screenDraw(screenWidth, screenHeight);
        credit->actions();
        glEnable(GL_LIGHTING);
        glPopMatrix();
    }
    if(help->current)
    {
        glPushMatrix();     //group object
        glScalef(3.33,3.33,1.0);
        glDisable(GL_LIGHTING);
        glTranslatef(help->xPos, help->yPos, help->zPos);
        help->screenDraw(screenWidth, screenHeight);  //draw model obj
        help->actions();
        glEnable(GL_LIGHTING);
        glPopMatrix();
    }
    if(game->current)
    {
        glPushMatrix();     //group object
        glScalef(3.33,3.33,1.0);
        glDisable(GL_LIGHTING);
        if(level1 || level2 || level3 || level4)
        {
            glPushMatrix();

            glDisable(GL_LIGHTING);

            p->parallaxDraw(screenWidth,screenHeight);
            glEnable(GL_LIGHTING);
            glPopMatrix();

// NOTE (Skele#1#): Comment out one of these at once to test different level music.
//Only works if done one at a time per compile. WILL switch when different levels are reached.

//HOW IT WORKS: spam spacebar to increase sndsIterator. When it reaches >3 different loop plays, when > 6 different loop plays.
//              spam tab to decrease sndsIterator. Do note that it's a bit slow when reducing.

//"It's not a bug, it's a feature" ~ someone at some point

            snds->firstGameSound(sndsIterator);
            //snds->secondGameSound(sndsIterator);
            //snds->thirdGameSound(sndsIterator);
        }
        if(player->playerSpawn)
        {

            glPushMatrix();

            glDisable(GL_LIGHTING);
            glEnable(GL_BLEND);
            player->drawPlayer();
            player->actions();
            glEnable(GL_LIGHTING);
            glPopMatrix();

        }
        glEnable(GL_LIGHTING);
        glPopMatrix();

        snds->stopMenu();
        //snds->playGameSound();

    }
    if(pause->current)
    {
        newgame->continue_button(w,h, screenWidth, screenHeight);
        glPushMatrix();     //group object
        glScalef(3.33,3.33,1.0);
        glDisable(GL_LIGHTING);
        glTranslatef(pause->xPos, pause->yPos, pause->zPos);
        pause->screenDraw(screenWidth, screenHeight);  //draw model obj
        pause->actions();
        glEnable(GL_LIGHTING);
        glPopMatrix();
    }
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    newgame->drawObject();
    newgame->actions();
    glEnable(GL_LIGHTING);
    glPopMatrix();      //exit group

    glPushMatrix();
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    guide->drawObject();
    guide->actions();
    glEnable(GL_LIGHTING);
    glPopMatrix();      //exit group

    glPushMatrix();
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    quit->drawObject();
    quit->actions();
    glEnable(GL_LIGHTING);
    glPopMatrix();      //exit group
/*
    for(int i=0; i<20; i++)
    {
        if(E[i].pos.x >3.5)
        {
            E[i].action =E[i].WALKLEFT;
            E[i].speed =-0.01;
            E[i].pos.y =-1.2;
            E[i].eRotate.z =0;
        }
        if(E[i].pos.x<-3.5)
        {
            E[i].action =E[i].WALKRIGHT;
            E[i].speed =0.01;
            E[i].pos.y =-1.2;
            E[i].eRotate.z =0;
        }
        //if (player->actionTrigger= player->ROLL) {}
        else if(hit->isRadialCollision(E[i].pos, player->plPosition,0.5,0.5,0.02))
        {
            {
                if(E[i].pos.x >3.5)
                {
                    E[i].action =E[i].WALKRIGHT;
                    E[i].speed =-0.01;
                }
                if(E[i].pos.x<-3.5)
                {
                    E[i].action =E[i].WALKLEFT;
                    E[i].speed =0.01;
                }
                /*
                player->hp =  player->hp-1;
                if (player->hp <= 0)
                {
                    player->playeralive = false; //optional player death
                    break;
                }

            }
            E[i].drawEnemy();
            E[i].actions();
        }
    }
    */
    return true;

}

GLvoid GLScene::resizeScene(GLsizei width, GLsizei height)
{
    GLfloat aspectRatio = (GLfloat)width/(GLfloat)height; // keep track of the ratio
    glViewport(0,0,width,height); // adjusting the viewport
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,aspectRatio,0.1,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    w = width;
    h = height;
}

int GLScene::windMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)   // check for inputs
    {
    case WM_KEYDOWN:
        kbMs->wParam = wParam;
        kbMs->keyPress(load, menu, help, game, pause, newgame, guide, quit, player, snds); // Pass screen instance

        kbMs->soundIterator(sndsIterator);
        break;

    case WM_KEYUP:
        kbMs->wParam = wParam;
        kbMs->keyUP(load, help, menu, game, pause, credit, player, newgame, guide, quit, snds);
        break;

    case WM_LBUTTONDOWN:
        kbMs->wParam = wParam;
        kbMs->mouseEventDown(load, menu, help, game, newgame, guide, quit, T, LOWORD(lParam), HIWORD(lParam));
        break;

    case WM_RBUTTONDOWN:

        break;

    case WM_LBUTTONUP:
        kbMs->mouseEventUp(load, menu, help, game, pause, player, newgame, guide, quit, T, LOWORD(lParam), HIWORD(lParam));
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:

        break;

    case WM_MOUSEMOVE:
        kbMs->wParam = wParam;
        kbMs->mouseMove(w, h, screenWidth, screenHeight, newgame, guide, quit, LOWORD(lParam), HIWORD(lParam));
        break;
    case WM_MOUSEWHEEL:


        break;
    }
}
