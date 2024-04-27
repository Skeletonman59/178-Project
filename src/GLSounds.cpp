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
    introMenu = engine->play2D("sounds/Menu/BeginningIntro.wav", false, true, true);
    if(introMenu) introMenu->setVolume(1);
    mainMenu = engine->play2D("sounds/Menu/MenuLoop.wav", true, true, true);
    if(mainMenu) mainMenu->setVolume(1);

    return 1;
}
