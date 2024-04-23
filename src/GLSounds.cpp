#include "GLSounds.h"



GLSounds::GLSounds()
{
    //ctor
}

GLSounds::~GLSounds()
{
    //dtor
    engine->drop();
}

void GLSounds::playMusic(char* File)
{
    engine->play2D(File, false);
}
void GLSounds::playMenuLoop(char* File, bool menuLoop)
{
    //wait 15 seconds
    if(menuLoop && menuLoopTriggerSwitch) {
        engine->play2D(File, true);
    }
    menuLoopTriggerSwitch = false; //nothing can change this now
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
    menuLoopTriggerSwitch = true;
    if(!engine){cout<<" ERROR: *** The Sound Engine Could Not Start"<<endl;
    return 0;}
    return 1;
}
