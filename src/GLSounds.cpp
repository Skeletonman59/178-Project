#include "GLSounds.h"



GLSounds::GLSounds()
{
    //ctor
}

GLSounds::~GLSounds()
{
    //dtor
    introMenu->drop();
    engine->drop();
}
void GLSounds::playMenu()
{
    if(introMenu->getIsPaused()) introMenu->setIsPaused(false);
    if(introMenu->isFinished()) mainMenu->setIsPaused(false);
}
void GLSounds::stopMenu()
{
    //I need to reset introMenu and mainMenu back to the beginning as if i never played them
    //TODO: fix stop
    if (introMenu)
    {
        introMenu->setIsPaused(true);
        introMenu->setPlayPosition(0);
    }
    if (mainMenu)
    {
        mainMenu->setIsPaused(true);
        mainMenu->setPlayPosition(0);
    }

}
void GLSounds::playGameSound()
{
    //if we on game screen, play music depending on level?

    //we want the audios to start at the same time
    Empty_1->setIsPaused(false);
    Active_1->setIsPaused(false);
    Main_1->setIsPaused(false);
    switch(GAME_ITERATOR)
    {
    case 0:
        Empty_1->setVolume(1);
        GAME_ITERATOR++;
        break;
    case 1:
        if(clock() - myTime->startTime>60)
        {
            ActVol += 0.01;
            Active_1->setVolume(ActVol);
            myTime->startTime =clock();
            GAME_ITERATOR++;
        }
        break;
    case 2:
        if(clock() - myTime->startTime>60)
        {
            MenuVol += 0.05;
            Main_1->setVolume(MenuVol);
            myTime->startTime =clock();
        }
        break;
    }
}

void GLSounds::playSound(char* File)
{
    if(!engine->isCurrentlyPlaying(File))
        engine->play2D(File, false,false);
}

void GLSounds::pauseSound(char* File)
{
    engine->play2D(File,true,false);
}

int GLSounds::initSounds()
{
    if(!engine)
    {
        cout<<" ERROR: *** The Sound Engine Could Not Start"<<endl;
        return 0;
    }
    ActVol = 0;
    MenuVol = 0;
    introMenu = engine->play2D("sounds/Menu/BeginningIntro.wav", false, true, true);
    mainMenu = engine->play2D("sounds/Menu/MenuLoop.wav", true, true, true);
    Empty_1 = engine->play2D("sounds/Game/lvl1/Empty.wav", true, true, true);
    Active_1 = engine->play2D("sounds/Game/lvl1/Active.wav", true, true, true);
    Main_1 = engine->play2D("sounds/Game/lvl1/Main.wav", true, true, true);
    TITT_2 = engine->play2D("sounds/Game/lvl2/Exposure-TITTGLoop.wav", true, true, true);
    Second_2 = engine->play2D("sounds/Game/lvl2/Exposure-2nd.wav", true, true, true);
    Full_2 = engine->play2D("sounds/Game/lvl2/Exposure-Full.wav", true, true, true);

    if(introMenu) introMenu->setVolume(1);
    if(mainMenu) mainMenu->setVolume(1);
    if(Empty_1) Empty_1->setVolume(0);
    if(Active_1) Active_1->setVolume(ActVol);
    if(Main_1) Main_1->setVolume(MenuVol);
    if(TITT_2) TITT_2->setVolume(0);
    if(Second_2) Second_2->setVolume(ActVol);
    if(Full_2) Full_2->setVolume(MenuVol);
    GAME_ITERATOR = 0;

    return 1;
}
