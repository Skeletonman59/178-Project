#include <GLScene.h>
#include<GLLight.h>
#include<GLTexture.h>
#include<GLInputs.h>
#include<GLParallax.h>
#include<GLPlayer.h>
#include<GLEnms.h>
#include<GLTimer.h>
#include<GLCheckCollision.h>
#include<Screen.h>
#include<Menu.h>
#include<Object.h>

GLInputs *kbMs = new GLInputs();    //keyboard and mouse
GLTimer *T = new GLTimer();
Screen *screen = new Screen();         //static screen object
Screen *help = new Screen();          //much like a second parallax, this is a separate screen object
Menu *menu = new Menu();            //menu with button locations
Object *arrow = new Object();       //moving arrow
bool reverseOsc = true;             //oscillator flag
bool playerSpawn = false;           //stops the player from spawning early
//Note: i kept the line above in case the player spawns right when screen transitions move.

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
    menu->menuInit("images/menu/mainMenu.png");
    screen->screenInit("images/menu/start.png");
    help->screenInit("images/menu/help.png");
    arrow->initObject(8,9, "images/menu/arrow.png");

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
    glTranslatef(0, 0, screen->zPos);
    screen->screenDraw(screenWidth, screenHeight);  //draw model obj
    glPopMatrix();

    //screen->blackFade(0.01);

    glPushMatrix();
    glScalef(3.33,3.33,1.0);
    glTranslatef(menu->xPos, 0, menu->zPos);           //zpos-1 puts menu behind screen
    menu->menuDraw(screenWidth, screenHeight);
    glPopMatrix();

    glPushMatrix();     //group object
    glScalef(3.33,3.33,1.0);
    glDisable(GL_LIGHTING);
    glTranslatef(help->xPos-4, 0, menu->zPos); //this essentially connects menu and help
    help->screenDraw(screenWidth, screenHeight);  //draw model obj
    //cout << screenWidth << " " << screenHeight << endl;

    glPopMatrix();

    glPushMatrix();
    glDisable(GL_LIGHTING);
    arrow->drawObject();
    glEnable(GL_LIGHTING);
    glPopMatrix();      //exit group

    //NOTE: keep this, this is so the player spawns after screen transitions ends
    if (playerSpawn)
    {
        glPushMatrix();
        glDisable(GL_LIGHTING);

        if(kbMs->screenToggle == kbMs->GAMESCREEN)
        {
            //pl->drawPlayer();
            //pl->actions();
        }
        glEnable(GL_LIGHTING);
        glPopMatrix();      //exit group
    }

    //Info: the first Enter/click will be resonsible for LoadingScreen fadeout
    if(kbMs->firstReturn)
    {
        if(clock() - T->startTime>30)
        {
            if  (screen->alpha < 1.0) screen->alpha+=0.1;
            else if (menu->zPos == 0.0) menu->alpha-=0.1; //screen already dark, we can make the menu pop in
            else
            {
                screen->zPos = -5.0;                       //MOVE screen BACK
                menu->zPos = 0.0;
            }
            if (menu->alpha > 1.0) kbMs->firstReturn = false;
            T->startTime =clock();
        }

    }

    //Info: moves the help screen and menu screen to the left
    if (kbMs->helpTransitioning)               //i guess this has to be done in the drawScene function
    {
        if(clock() - T->startTime>10)
        {
            help->xPos +=0.1;
            menu->xPos +=0.1;

            if (help->xPos >= 4.0)    //yes its a sentinel value, no better way of fixing?
            {
                help->xPos = 4; // Ensure it stops at the correct position
                kbMs->helpTransitioning = false; // Reset transitioning flag
            }
            T->startTime =clock();
        }
    }
    //info: un-does function above
    if (kbMs->menuTransitioning)               //i guess this has to be done in the drawScene function
    {
        if(clock() - T->startTime>10)
        {
            help->xPos -=0.1;
            menu->xPos -=0.1;

            if (help->xPos <= 0.0f)    //yes its a sentinel value, no better way of fixing?
            {
                help->xPos = 0; // Ensure it stops at the correct position
                kbMs->menuTransitioning = false; // Reset transitioning flag
            }
            T->startTime =clock();
        }
    }
    //Info: menu gimmick, responsible for arrow movement
    if (kbMs->arrowOscillate)
    {

        if(clock() - T->startTime>10)
        {
            //change arrow objectPosition.x
            //cout << reverseOsc << endl;
            if(!reverseOsc)
            {
                arrow->objPosition.x-=0.0025;
                if(arrow->objPosition.x <= -0.60) reverseOsc = true;
            }
            else
            {
                arrow->objPosition.x+=0.0025;
                if(arrow->objPosition.x >= -0.53) reverseOsc = false;
            }

            T->startTime = clock();
        }
    }
    //Note: kept this for the same reason as playerSpawn
    /*
    if (kbMs->bgSummon)//this worked in arrow oscillate for some reason
    {
        arrow->objPosition.y = 5; //get arrow away
        //arm->objPosition.y = 0;
        if(clock() - T->startTime>5)
        {
            //alpha 0 means visible
            if (menu->alpha < 1.0) menu->alpha+=0.1;
            else if(bg->zPos == 0.0) bg->alpha-=0.1;
            else
            {
                menu->zPos = -1.0;
                bg->zPos = 0.0;

            }
            if (bg->alpha < 0.50)
            {
                kbMs->bgSummon = false;
                playerSpawn = true;
            }
            T->startTime =clock();
        }

    }
    */
    /*
    //Note: transitions game back to menu, worry about when making the full game
    if (kbMs->gameToMenu)
    {
        if(clock() - T->startTime>5)
        {
            //alpha 0 means visible

            if (bg->alpha < 1.0) bg->alpha+=0.1;
            else if(bg->zPos == -2.0) menu->alpha-=0.1;
            else
            {
                menu->zPos = 0.0;
                bg->zPos = -2.0;
            }
            if (menu->alpha < 0.1)
            {
                playerSpawn = false;
                kbMs->gameToMenu = false;

            }
            T->startTime =clock();

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
}

int GLScene::windMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
    switch(uMsg)   // check for inputs
    {
    case WM_KEYDOWN:
        kbMs->wParam = wParam;
          kbMs->keyPress(screen, menu); // Pass screen instance
          //kbMs->keyBackground(plx, 0.005);
          //kbMs->keyBackground(plx1, 0.01);
         break;

    case WM_KEYUP:
        kbMs->wParam = wParam;
        kbMs->keyUP();
         break;

    case WM_LBUTTONDOWN:
        kbMs->wParam = wParam;
        kbMs->mouseEventDown(menu, help, arrow, T, LOWORD(lParam), HIWORD(lParam));
         break;

    case WM_RBUTTONDOWN:

         break;

    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:

        break;

    case WM_MOUSEMOVE:
        kbMs->wParam = wParam;
        kbMs->mouseMove(menu, help, arrow, LOWORD(lParam), HIWORD(lParam));
         break;
    case WM_MOUSEWHEEL:


       break;
    }
}


