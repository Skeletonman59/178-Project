#include <GLScene.h>
#include<GLLight.h>
#include<GLTexture.h>
#include<GLModel.h>
#include<GLInputs.h>
#include<GLParallax.h>
#include<GLPlayer.h>
#include<GLEnms.h>
#include<GLTimer.h>
#include<GLCheckCollision.h>

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
    glEnable(GL_TEXTURE_2D);  //enable textures

    GLLight Light(GL_LIGHT0);
    Light.setLight(GL_LIGHT0);

    glEnable(GL_BLEND);             // Transparent effect of pngs
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    if(level1)
    {
    float curr = -1.0;  // Used to spread out enemies and prevent overlap

    float interval =0.5;        //used to spread out enemies

    p->parallaxInit("images/stage1.png");
    player->initPlayer(4,4,"images/princess.png");
    health->initHealth(2,6,"images/health.png");
    enmsTex->loadTexture("images/tent.png");
    health->statusTrigger =0;


    for(int i=0;i<10;i++)
    {
        E[i].pos.x = curr;// Place first enemy after player
        E[i].pos.y= 0.9;   //All will start at the top
        E[i].eScale.x = E[i].eScale.y = 5.0/30.0;
        curr+=interval;
    }
    doneLoading = true;
    }



    if(level2)
    {
    health->statusTrigger =0;       //Reset health bar
    p->parallaxInit("images/stage2.png");
    enmsTex->loadTexture("images/ball.png");
   player->initPlayer(4,4,"images/princess.png");

      for(int i=0;i<15;i++)             //more enemies
    {                                  //Enemies will now spawn random location and move faster
        E[i].speed = .04;
        E[i].pos.x=(float)rand()/float(RAND_MAX) * 5-1.2;
        E[i].pos.y=(float)rand()/float(RAND_MAX) * 5-1.2;
        E[i].eScale.x = E[i].eScale.y = 3.0/30.0;//(float)(rand() % 12) / 30.0;

    }
    doneLoading = true;
    }



    if(level3)
    {
    health->statusTrigger =0; // Reset Health

    p->parallaxInit("images/stage3.png");
        enmsTex->loadTexture("images/crab.png");

    player->initPlayer(4,4,"images/princess.png");

       for(int i=0;i<20;i++)             // More enemies
    {                                    // Enemies will spawn randomly
        E[i].pos.x = (float)rand()/float(RAND_MAX) * 5-1.35;;
        E[i].pos.y=(float)rand()/float(RAND_MAX) * 5-1.35;
        E[i].eScale.x = E[i].eScale.y = 5.0/30.0;

    }
    doneLoading = true;
    }


    if(level4)          //Done screen
    {
    p->parallaxInit("images/last.png");
    player->initPlayer(4,4,"images/princess.png");
    health->statusTrigger =0;

    doneLoading = true;
    }

    return true;
}

void GLScene::drawGame(int n)
{
    for(int i=0;i< n;i++)       // Loop runs for given enemy amount
   {
       if(level1 || level2){            // For level 1-2 if bottom reached go up
       if(E[i].pos.y <=-0.5){
                E[i].action = 4;
        }
        if(E[i].pos.y>0.9)              //If reached top, go down
       {

           E[i].action = 2;

       }
       }

        if(level3){
       if(E[i].rightBound()){            // if right wall -> bounce left and up
        E[i].action =5;
       }
       if(E[i].leftBound()){              // if left wall -> bounce right and up
        E[i].action =6;
       }

        if(E[i].pos.y>0.9)                     // Random L or R bounce down
       {
           int x = rand() % 2;
           x+=7;
           E[i].action = x;

       }
        if(E[i].pos.y<-0.5)        // Random L or R bounce up
       {
           int x = rand() % 2;
           x+=5;
           E[i].action = x;

       }
        }
       if(hit->isRadialCollision(player->plPosition,E[i].pos,0.01,0.01,0.1) )
       {
           health->statusTrigger +=1;              // Update health after each hit
           E[i].action =4;                         //if hit, enemy will go up
           if(health->statusTrigger ==5) {          // If 5 hits, restart
            health->statusTrigger=0;
            player->plPosition.x =-1.3;
            player->plPosition.y =-0.475;
            player->plPosition.z = -1.0;
           }
       }


       E[i].drawEnemy();
       E[i].actions();
       glEnable(GL_LIGHTING);
   }
   glPopMatrix();

}

GLint GLScene::drawScene()   // this function runs on a loop
                              // DO NOT ABUSE ME
{
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);// clear bits in each itterration
   glLoadIdentity();
   glColor3f(1.0,0.0,0.0);     //color the object red

   glPushMatrix();
       glScalef(3.33,3.33,1.0);
       glDisable(GL_LIGHTING);


       p->parallaxDraw(screenWidth,screenHeight);
       glEnable(GL_LIGHTING);
       glPopMatrix();

       glPushMatrix();
       glDisable(GL_LIGHTING);
       player->drawPlayer();

       player->actions();
       glEnable(GL_LIGHTING);


   glPopMatrix();

   glPushMatrix();
   enmsTex->bindTexture();
   glDisable(GL_LIGHTING);

   if(level1){ drawGame(10);}  // draw game based on level
   else if(level2){ drawGame(15);}
    else if(level3){ drawGame(15);}





glPushMatrix();
    glScalef(3.33,3.33,1.0);
      glDisable(GL_LIGHTING);
       health->drawHealth();
          health->status();
       glEnable(GL_LIGHTING);




    glPopMatrix();
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
        KbMs->wParam=wParam;
        KbMs->keyPress(m,player);

         break;

    case WM_KEYUP:
        KbMs->wParam=wParam;
        KbMs->keyUP(player);


         break;

    case WM_LBUTTONDOWN:

         break;

    case WM_RBUTTONDOWN:

         break;

    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
        KbMs->mouseEventUp();

        break;

    case WM_MOUSEMOVE:

         break;
    case WM_MOUSEWHEEL:


       break;
    }
}


