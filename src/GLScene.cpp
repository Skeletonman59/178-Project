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
#include<GLProjectile.h>

//FINAL NOTES: the only additions this game needs are:
//A shop
//A bool array
//A variable resetter for gameover to newgame

//Approach ideas:
//Shop:
//no actual screen menu with button inputs, instead a loony shop drops from the sky
//onto the center of the screen. If the player jumps on the shop, a big Screen zooms
//in from the Z axis and shows what Upgrades are available. Each upgrade will be a
// different key to save on time

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

    deleted.x =999.0; // use dest to shoot right
    deleted.y =999.0;
    deleted.z = 999.0;

    glEnable(GL_TEXTURE_2D);  //enable textures
    load->screenInit( 0, 0,  0, 0, "images/menu/loadmenu.png");
    menu->screenInit( 0, 0, -1, 1, "images/menu/2.png");
    help->screenInit(-4, 0, 0.01, 0, "images/menu/helpmenu.png"); //seriously, who's gonna tell the help menu is 0.01 units closer?
    pause->screenInit(0, 0, 0, 0, "images/menu/pause.png");
    over->screenInit(0,0,0,0,"images/game/gameOver.png");
    credit->screenInit(0,0,0,0,"images/menu/creators.png");
    BulletTex->loadTexture("images/game/bullet.png");
    CoinTex->loadTexture("images/game/coin.png");

    load->current = true;

    //                x  y   z  a

    newgame->initObject(-2,0.11,0,2,5, "images/menu/buttons.png");
    //newgame->new_button(w,h, screenWidth, screenHeight);
    guide->initObject(-2,-0.08,0,2,5, "images/menu/buttons.png");
    guide->guide_button(w,h, screenWidth, screenHeight);
    quit->initObject(-2,-0.27,0,2,5, "images/menu/buttons.png");
    quit->quit_button(w,h, screenWidth, screenHeight);
    health->initObject(-0.6,0.5,0,5,9, "images/game/healthBarSprite.png");
    health->health_bar(w, h, screenWidth, screenHeight);
    bullet->initObject(0, 0, -6, 1,2, "images/game/bullet.png");
    bullet->default_obj();

    snds->initSounds();
    snds->myTime->startTime = clock();

    T->startTime = clock();

    player->initPlayer(5,5,"images/sprites/Player.png");
    Iframe->startTime = clock();
    enmTexture[0].loadTexture("images/sprites/Enemy01.png");
    enmTexture[1].loadTexture("images/sprites/Enemy02.png");
    enmTexture[2].loadTexture("images/sprites/Enemy03.png");
    for(int i=0; i<20; i++)
    {
        E[i].isEnemyLive = false;
        E[i].tex = &enmTexture[(rand() % 3)];
        int wallspawn = (rand()%99);
        if (wallspawn >50) E[i].pos.x = 5.0f;
        else E[i].pos.x = -5.0f;
        E[i].pos.y =-1.5;
        E[i].action = E[i].WALKLEFT;
        E[i].eScale.x = E[i].eScale.y = 0.5;
    }
// TODO (Skele#7#): An idea for enemy use: have a separate array that stores bools per index,
//if an enemy has been defeated then the bool is turned false. that way, when we iterate through
//the bool array, if the enemy has already been killed, don't use it and skip ahead?
//
//This would mean that enemy array size = maxNms1+2+3+4.

    enmSpawnRate = (float)rand()/(float)RAND_MAX*100 + 150;
    enmN = 0;

    for(int i = 0; i < 6; i++)
    {
        P[i].initBullet();
    }
    for(int i = 0; i < 100; i++)
    {
        coin[i].initCoin();
    }

    if(level1)
    {
        p->parallaxInit("images/game/night.png");
        doneLoading=true;
        maxEnms = 5;
        /*for(int i=0; i<20; i++)
            {
                E[i].enemyHealth = 4;
                E[i].speed = 0.05;
            }*/
    }
    if(level2)
    {
        //snds->stopGameSound();
        p->parallaxInit("images/game/lava.jpg");
        doneLoading=true;
        maxEnms = 10;
        for(int i=0; i<20; i++)
        {
            E[i].enemyHealth = 3;
            E[i].speed = 0.065;

        }

    }
    if(level3)
    {
        //snds->stopGameSound();
        p->parallaxInit("images/game/forest.png");
        doneLoading=true;
        maxEnms = 15;
        for(int i=0; i<20; i++)
        {
            E[i].enemyHealth = 7;
            E[i].speed = 0.030;
            E[i].eScale.x =1.5;
            E[i].eScale.y =1.5;
            E[i].pos.y+=0.5;
            E[i].radius = 1.0;
        }
    }
    if(level4)
    {
        //snds->stopGameSound();
        p->parallaxInit("images/game/stage3.png"); //placeholder
        doneLoading=true;
        maxEnms = 20;

        for(int i=0; i<20; i++)
        {
            //E[i].x
            E[i].enemyHealth = 10;
            E[i].speed = 0.1;
            E[i].eScale.x =2.0;
            E[i].eScale.y =2.0;
            E[i].radius = 2.0;
            E[i].pos.y+=1;
        }


    }
    Ammo=6;
    Gold=0;
    coinIter=0;
    goal = 0;
    iframeValue = 1000;
    damage = 1;
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
        // find a way to re-init everything?
        //thoughts: a function similar to initGL(), that only reloads
        //things like variables and not objects or screens. does NOT
        //initialize them, just resets them.
// TODO (Skele#1#): WORK ON A FUNCTION THAT RESETS NON-OBJECT ITEMS,
//AND RESETS OBJECT ITEMS TO THEIR ORIGINAL POSITIONS WITHOUT RE-INITIALIZING THEM

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
        //object tester
        /*
        glPushMatrix();
        glDisable(GL_LIGHTING);
        glEnable(GL_BLEND);
        bullet->drawObject();
        glEnable(GL_LIGHTING);
        glDisable(GL_BLEND);
        glPopMatrix();
        */

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
        glEnable(GL_LIGHTING);
        glPopMatrix();

        if(player->playerSpawn == true/*&& kbMs->screenToggle == GAMESCREEN*/ )
        {
            glPushMatrix();
            glDisable(GL_LIGHTING);
            glEnable(GL_BLEND);
            player->drawPlayer();
            player->actions();
            glEnable(GL_LIGHTING);
            glPopMatrix();
        }

        bool coinSpawned = false;
        enmSpawnRate--;
        if(enmSpawnRate <= 0)
        {
            E[enmN++].isEnemyLive = true;
            if(enmN >= maxEnms);
            enmN %= maxEnms;
            enmSpawnRate = (float)rand()/(float)RAND_MAX*100; //+ 1350;
        }

        //if(1==1/*if the shop icon is clicked      */)
        /* {
             if(coinIter>31 && kbMs->unlockedRoll == false)// this is an example; it unlocks roll
             {
                 kbMs->unlockedRoll = true;
                 coinIter = (coinIter - 30);
             }
             if(coinIter>6){
              iframeValue = (iframeValue + 500);
             coinIter = (coinIter - 5);

             }
                  if(coinIter>11){
              damage = (damage + 1);
             coinIter = (coinIter - 10);

         }

         }
        */
        for(int i = 0; i < maxEnms; i++)
        {
            //glEnable(GL_BLEND);
            //enmTexture[2].bindTexture();
            if(E[i].isEnemyLive)
            {
                E[i].pos.x < player->plPosition.x ? E[i].action = E[i].WALKRIGHT : E[i].action = E[i].WALKLEFT;
            }
            if(hit->isRadialCollision(E[i].pos, player->plPosition,E[i].radius,0.2,0.02)) //ENEMY ON PLAYER
            {
                if((clock() - Iframe->startTime) > iframeValue && player->actionTrigger != player->ROLL )
                {
                    player->hp =  player->hp-1;
                    player->hit = true;
                    E[i].pos.x < player->plPosition.x ? player->direction = 1 : player->direction = -1;
                    player->xMin = 1.0f/player->framesX;
                    player->xMax = 2.0f/player->framesX;
                    player->yMin = 3.0f/player->framesY;
                    player->yMax = 4.0f/player->framesY;
                    if(health->barTrigger != health->EMPTY )health->barTrigger = health->barTrigger + 1;
                    //cout << health->barTrigger << endl;
                    cout << player->hp << endl;
                    if (player->hp <= 0)
                    {
                        player->playeralive = false;
                        over->current = true;
                    }
                    //cout<<"player current hp is " << player-> hp <<endl;

                    Iframe->startTime = clock();
                }
            }
            for(int j = 0; j < 6; j++) // projectile count
            {
                if(hit->isRadialCollision(E[i].pos, P[j].pos,0.2,0.2,0.02) && E[i].isEnemyLive == true) //ENEMY ON BULLET
                {
                    E[i].enemyHealth = E[i].enemyHealth - damage;
                    P[j].isLive=false;
                    P[j].pos = deleted;
                    if (E[i].enemyHealth <= 0)
                    {
                        coin[coinIter].PlaceItem(E[i].pos);
                        E[i].isEnemyLive = false;
                        E[i].pos=deleted; // coins do spawn but we need to remove the enemies, cant do both at the same time
                        coin[coinIter].coinSpawn = true;
                        coinIter++;
                    }
                }
            }


            E[i].drawEnemy();
            E[i].actions();

        }


        snds->stopMenu();
        //snds->playGameSound();

        if(player->playerSpawn)
        {
            glPushMatrix();
            glDisable(GL_LIGHTING);
            glEnable(GL_BLEND);
            health->drawObject();
            health->barActions();
            glEnable(GL_LIGHTING);
            glDisable(GL_BLEND);
            glPopMatrix();
        }

        if(level1 && goal != maxEnms)
        {
            snds->firstGameSound(health->barTrigger);

        }
        else if(level2 && goal != maxEnms)
        {
            snds->secondGameSound(health->barTrigger);
        }
        else if(level3 && goal != maxEnms)
        {
            snds->thirdGameSound(health->barTrigger);
        }
        else if(level4 && goal != maxEnms)
        {
            snds->fourthGameSound(health->barTrigger);
        }

        BulletTex->bindTexture();
        if (player->shooting == true && Ammo > 0)
        {
            Ammo--;

            //P[Ammo].drawProjectile(player->plPosition);
            P[Ammo].isLive=true;
            player->shooting = false;
            //P[Ammo].playerShootSet(player->plPosition);
            P[Ammo].drawProjectile(player->plPosition);

        }

        glPushMatrix();
        glDisable(GL_LIGHTING);
        glEnable(GL_BLEND);
        for (int i = 0; i < 6; i++)
        {
            if(P[i].isLive == true)
            {
                P[i].anotherTime->startTime = clock();
                P[i].drawProjectileStatic();
                P[i].bulletMove(player->direction, deleted);
                //P[i].isExpire();
                //P[i].ThrowProjectile(player->plPosition,P[i].dest,1.0, 1); // use this to shoot right
                //P[Ammo].ThrowProjectile(player->plPosition,P[Ammo].dest2,1.0); // use this to shoot left
            }
            if(Ammo == 0)
            {
                //reload condition
                Ammo=6;
            }
        }
        glEnable(GL_LIGHTING);
        glPopMatrix();

        CoinTex->bindTexture();
        glPushMatrix();
        glDisable(GL_LIGHTING);
        glEnable(GL_BLEND);
        for (int i = 0; i < 100; i++)
        {
            if (coin[i].coinSpawn)
            {
                coin[i].drawItem(); // Draw the coin
            }
        }
        glEnable(GL_LIGHTING);
        glPopMatrix();

        for(int k = 0; k < coinIter; k++)
        {
            //COMMENT THIS OUT IF YOU DO NOT LIKE HAVING AUTO-COINS
            if(player->plPosition.x > coin[k].pos.x ) coin[k].pos.x +=0.01;
            else if (player->plPosition.x < coin[k].pos.x ) coin[k].pos.x -=0.01;

            if(hit->isRadialCollision(coin[k].pos, player->plPosition,0.15,0.15,0.2))
            {
                coin[k].PlaceItem(deleted); //pos=deleted;
                coin[k].coinSpawn=false;
                Gold++;
                goal++;
                //cout<<"gold aquired"<<endl;

            }
        }

    }
    if(over->current)
    {
        game->current = false;
        player->playerSpawn = false;
        snds->stopGameSound();
        kbMs->screenToggle = kbMs->GAMEOVER; //i forgot how this was applied

        glPushMatrix();
        glScalef(3.33,3.33,1.0);
        glDisable(GL_LIGHTING);
        glTranslatef(over->xPos, over->yPos, over->zPos);
        over->screenDraw(screenWidth, screenHeight);
        over->actions();
        glEnable(GL_LIGHTING);
        glPopMatrix();

    }
    if(pause->current)
    {
        newgame->continue_button(w,h, screenWidth, screenHeight);
        glPushMatrix();     //group object
        glScalef(3.33,3.33,1.0);
        glDisable(GL_LIGHTING);
        player->playerSpawn = false;
        for(int i=0; i<77; i++)
        {
            E[i].isEnemyLive = false;

        }
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
    glDisable(GL_BLEND);
    glPopMatrix();      //exit group

    glPushMatrix();
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    guide->drawObject();
    guide->actions();
    glEnable(GL_LIGHTING);
    glDisable(GL_BLEND);
    glPopMatrix();      //exit group

    glPushMatrix();
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    quit->drawObject();
    quit->actions();
    glEnable(GL_LIGHTING);
    glDisable(GL_BLEND);
    glPopMatrix();      //exit group

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
        kbMs->keyPress(load, menu, help, game, pause, newgame, guide, quit, player, snds, over); // Pass screen instance
        kbMs->keyBackground(p, 0.001);
        break;

    case WM_KEYUP:
        kbMs->wParam = wParam;
        kbMs->keyUP(load, help, menu, game, pause, credit, player, newgame, guide, quit, health, snds, over);
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
