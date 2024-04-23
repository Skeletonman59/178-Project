#include<GLScene.h>
#include<GLLight.h>
#include<GLTexture.h>
#include<GLInputs.h>
#include<GLTimer.h>
#include<Screen.h>
#include<Object.h>
#include<GLSounds.h>

GLInputs *kbMs = new GLInputs();    //keyboard and mouse
GLTimer *T = new GLTimer();
Screen *load = new Screen();         //static screen object
Screen *help = new Screen();         //much like a second parallax, this is a separate screen object
Screen *menu = new Screen();         //screen with button locations

Object *newgame = new Object();
Object *guide = new Object();
Object *quit = new Object();

GLSounds *snds = new GLSounds();


GLScene::GLScene()
{
    //ctor

    screenWidth  = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
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
    load->screenInit( 0, 0,  0, 0, "images/menu/start.png");
    menu->screenInit( 0, 0, -1, 1, "images/menu/mainMenuScreen.png");
    help->screenInit(-4, 0, 0, 0, "images/menu/help.png");
    //                x  y   z  a

    newgame->initObject(-2,0.11,0,2,5, "images/menu/buttons.png");
    newgame->new_button(w,h, screenWidth, screenHeight);
    guide->initObject(-2,-0.08,0,2,5, "images/menu/buttons.png");
    guide->guide_button(w,h, screenWidth, screenHeight);
    quit->initObject(-2,-0.27,0,2,5, "images/menu/buttons.png");
    quit->quit_button(w,h, screenWidth, screenHeight);

    snds->initSounds();
    snds->playMusic("sounds/Menu/BeginningIntro.wav");
    snds->myTime->startTime = clock();

    menuLoopTrigger = true;

    T->startTime = clock();

    return true;
}

GLint GLScene::drawScene()    // this function runs on a loop
// DO NOT ABUSE ME
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);// clear bits in each iteration
    glLoadIdentity();
    glColor3f(1.0,1.0,1.0);     //color the object red

    glPushMatrix();     //group object
    glScalef(3.33,3.33,1.0);
    glDisable(GL_LIGHTING);
    glTranslatef(load->xPos, load->yPos, load->zPos);
    load->screenDraw(screenWidth, screenHeight);  //draw model obj
    load->actions();
    glPopMatrix();

    glPushMatrix();
    glScalef(3.33,3.33,1.0);
    glTranslatef(menu->xPos, load->yPos, menu->zPos);
    menu->screenDraw(screenWidth, screenHeight);
    menu->actions();
    glPopMatrix();

    glPushMatrix();     //group object
    glScalef(3.33,3.33,1.0);
    glDisable(GL_LIGHTING);
    glTranslatef(help->xPos, help->yPos, menu->zPos);
    help->screenDraw(screenWidth, screenHeight);  //draw model obj
    help->actions();
    glPopMatrix();

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
    glPopMatrix();      //exit group

    if(clock() - snds->myTime->startTime > 14500) snds->playMenuLoop("sounds/Menu/MenuLoop.wav", menuLoopTrigger);
    //TODO: TWO BOOLS? one bool that flicks the above on, another that is always on, that gets flicked off after function
    //ends, music line starts only if both bools are on.

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
          kbMs->keyPress(load, menu, help, newgame, guide, quit); // Pass screen instance
         break;

    case WM_KEYUP:
        kbMs->wParam = wParam;
        kbMs->keyUP(load, help, menu, newgame, guide, quit);
         break;

    case WM_LBUTTONDOWN:
        kbMs->wParam = wParam;
        kbMs->mouseEventDown(load, menu, help, newgame, guide, quit, T, LOWORD(lParam), HIWORD(lParam));
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
