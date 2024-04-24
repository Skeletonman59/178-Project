#include <common.h>
#include<GLScene.h>
#include<GLLight.h>
#include<GLParallax.h>
#include<GLPlayer.h>
#include<GLInputs.h>
#include<GLTexture.h>
#include<GLEnms.h>
#include<GLTimer.h>
#include<GLCheckCollision.h>
#include<GLSound.h>
GLScene::GLScene()
{
    //ctor

    screenWidth  = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    level1=  true;   //Used to switch through screens
    level2= false;
    level3=false;
    level4=false;
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
    menu->screenInit( 0, 0, 0, 0, "images/menu/2.png");
    help->screenInit(0, 0, 0, 0, "images/menu/helpmenu.png");
    pause->screenInit(0, 0, 0, 0, "images/menu/pause.png");
    credit->screenInit(0,0,0,0,"images/menu/creators.png");


    //                x  y   z  a
    player->initPlayer(4,4,"images/menu/poke.png");


    newgame->initObject(-2.0,0.11,0,2,5, "images/menu/buttons.png");
    newgame->button(w,h,screenWidth,screenHeight,500,265,365,1.0);

    guide->initObject(-2.0,-0.08,0,2,5, "images/menu/buttons.png");
    guide->button(w,h,screenWidth,screenHeight,500,385,480,2.0);

    quit->initObject(-2.0,-0.27,0,2,5, "images/menu/buttons.png");
    quit->button(w,h,screenWidth,screenHeight,500,490,585,3.0);


    if(level1){ p->parallaxInit("images/menu/stage1.png"); doneLoading=true;}
    if(level2){ p->parallaxInit("images/menu/stage2.png"); doneLoading=true;}
    if(level3){ p->parallaxInit("images/menu/stage3.png"); doneLoading=true;}
    if(level4){ p->parallaxInit("images/menu/stage4.png"); doneLoading=true;}

    snds->initSound();
    snds->playMusic("sounds/Menu/BeginningIntro.wav");
    snds->myTime->startTime = clock();
    menuLoopTrigger = true;


load->current= true;
    T->startTime = clock();
    return true;
}

GLint GLScene::drawScene()    // this function runs on a loop
// DO NOT ABUSE ME
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);// clear bits in each iteration
    glLoadIdentity();
    //glColor3f(1.0,1.0,1.0);     //color the object red


if(load->current){
   glPushMatrix();     //group object
    glScalef(3.33,3.33,1.0);
    glDisable(GL_LIGHTING);
    glTranslatef(load->xPos, load->yPos, load->zPos);
    load->screenDraw(screenWidth, screenHeight);  //draw model obj
    load->actions();
       if(clock() - snds->myTime->startTime > 14500) snds->playMenuLoop("sounds/Menu/MenuLoop.wav", menuLoopTrigger);
    //TODO: TWO BOOLS? one bool that flicks the above on, another that is always on, that gets flicked off after function
    //ends, music line starts only if both bools are on.
     glEnable(GL_LIGHTING);
    glPopMatrix();
}

glPushMatrix();
    glDisable(GL_LIGHTING);
    newgame->drawObject();
    newgame->actions();
    glEnable(GL_LIGHTING);
glPopMatrix();      //exit group

glPushMatrix();
    glDisable(GL_LIGHTING);
    guide->drawObject();
    guide->actions();
    glEnable(GL_LIGHTING);
glPopMatrix();      //exit group

glPushMatrix();
    glDisable(GL_LIGHTING);
    quit->drawObject();
    quit->actions();
    glEnable(GL_LIGHTING);
glPopMatrix();
       //exit group

if(menu->current){
    glPushMatrix();
    glScalef(3.33,3.33,1.0);
     glDisable(GL_LIGHTING);
    glTranslatef(menu->xPos, menu->yPos, menu->zPos);
    menu->screenDraw(screenWidth, screenHeight);
    menu->actions();
       glEnable(GL_LIGHTING);
   glPopMatrix();
}

if(credit->current){
    glPushMatrix();
    glScalef(3.33,3.33,1.0);
     glDisable(GL_LIGHTING);
    glTranslatef(credit->xPos, credit->yPos, credit->zPos);
    credit->screenDraw(screenWidth, screenHeight);
    credit->actions();
       glEnable(GL_LIGHTING);
   glPopMatrix();
}
if(help->current){
    glPushMatrix();     //group object
    glScalef(3.33,3.33,1.0);
    glDisable(GL_LIGHTING);
    glTranslatef(help->xPos, help->yPos, help->zPos);
    help->screenDraw(screenWidth, screenHeight);  //draw model obj
    help->actions();
     glEnable(GL_LIGHTING);
    glPopMatrix();
}


if(game->current ){
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

    }
     if(player->playerSpawn){

       glPushMatrix();

       glDisable(GL_LIGHTING);
       player->drawPlayer();
       player->actions();
       glEnable(GL_LIGHTING);
        glPopMatrix();

   }
    glEnable(GL_LIGHTING);
  glPopMatrix();

}


if(pause->current){
    glPushMatrix();     //group object
    glScalef(3.33,3.33,1.0);
    glDisable(GL_LIGHTING);
    glTranslatef(pause->xPos, pause->yPos, pause->zPos);
    pause->screenDraw(screenWidth, screenHeight);  //draw model obj
    pause->actions();
      glEnable(GL_LIGHTING);
 glPopMatrix();

}




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
        kbMs->keyPress(load, menu, help,game,pause ,newgame, guide, quit,player); // Pass screen instance
         break;

    case WM_KEYUP:
        kbMs->wParam = wParam;
        kbMs->keyUP(load, help, menu,game,pause,credit,player, newgame, guide, quit);
         break;

    case WM_LBUTTONDOWN:
        kbMs->wParam = wParam;
        kbMs->mouseEventDown(load, menu, help,game, newgame, guide, quit, T, LOWORD(lParam), HIWORD(lParam));
         break;

    case WM_RBUTTONDOWN:

         break;

    case WM_LBUTTONUP:
        kbMs->mouseEventUp(load, menu, help, newgame, guide, quit, T, LOWORD(lParam), HIWORD(lParam));
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
