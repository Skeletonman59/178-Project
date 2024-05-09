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
void GLSounds::firstGameSound(int zCount) //bcs we don't know if we're doing it by kills or zombies present.
{
    //we want the audios to start at the same time
    Genesis_1->setIsPaused(false);
    Genesis_2->setIsPaused(false);
    Genesis_3->setIsPaused(false);
    if (zCount <= 1)
    {
        if(clock() - myTime->startTime>15)
        {
            Genesis_1->setVolume(1);

            if(secondVol != 0) secondVol -= 0.1;
            Genesis_2->setVolume(secondVol);

            if(thirdVol != 0) thirdVol -= 0.1;
            Genesis_3->setVolume(thirdVol);
            myTime->startTime =clock();
        }
    }
    else if (zCount == 2)
    {
        if(clock() - myTime->startTime>15)
        {
            if(secondVol != 1)secondVol += 0.1;
            Genesis_2->setVolume(secondVol);

            if(thirdVol != 0) thirdVol -= 0.1;
            Genesis_3->setVolume(thirdVol);

            myTime->startTime =clock();
        }
    }
    else if (zCount >= 3 )
    {
        if(clock() - myTime->startTime>15)
        {
            if(secondVol != 0) secondVol -= 0.1;
            Genesis_2->setVolume(secondVol);

            if(thirdVol != 1) thirdVol += 0.1;
            Genesis_3->setVolume(thirdVol);

            myTime->startTime =clock();
        }
    }
}
void GLSounds::secondGameSound(int zCount)
{
    Genesis_1->setIsPaused(true);
    Genesis_2->setIsPaused(true);
    Genesis_3->setIsPaused(true);

    Exposure_1->setIsPaused(false);
    Exposure_2->setIsPaused(false);
    Exposure_3->setIsPaused(false);
    if (zCount <= 1)
    {
        if(clock() - myTime->startTime>15)
        {
            Exposure_1->setVolume(1);

            if(secondVol != 0) secondVol -= 0.1;
            Exposure_2->setVolume(secondVol);

            if(thirdVol != 0) thirdVol -= 0.1;
            Exposure_3->setVolume(thirdVol);
            myTime->startTime =clock();
        }

    }
    else if (zCount == 2)
    {
        if(clock() - myTime->startTime>15)
        {
            if(secondVol != 1)secondVol += 0.1;
            Exposure_2->setVolume(secondVol);

            if(thirdVol != 0) thirdVol -= 0.1;
            Exposure_3->setVolume(thirdVol);

            myTime->startTime =clock();
        }
    }
    else if (zCount >= 3 )
    {
        if(clock() - myTime->startTime>15)
        {
            if(secondVol != 0) secondVol -= 0.1;
            Exposure_2->setVolume(secondVol);

            if(thirdVol != 1) thirdVol += 0.1;
            Exposure_3->setVolume(thirdVol);

            myTime->startTime =clock();
        }
    }
}

void GLSounds::thirdGameSound(int zCount)
{
    //TODO: ADD THIRD SOUND
    Stubborn_1->setIsPaused(false);
    Stubborn_2->setIsPaused(false);
    Stubborn_3->setIsPaused(false);
    if (zCount <= 1)
    {
        if(clock() - myTime->startTime>15)
        {
            if(firstVol != 1) firstVol += 0.1;
            Stubborn_1->setVolume(firstVol);

            if(secondVol != 0) secondVol -= 0.1;
            Stubborn_2->setVolume(secondVol);

            if(thirdVol != 0) thirdVol -= 0.1;
            Stubborn_3->setVolume(thirdVol);
            myTime->startTime =clock();
        }

    }
    else if (zCount == 2)
    {
        if(clock() - myTime->startTime>15)
        {
            if(firstVol != 0) firstVol -= 0.1;
            Stubborn_1->setVolume(firstVol);

            if(secondVol != 1)secondVol += 0.1;
            Stubborn_2->setVolume(secondVol);

            if(thirdVol != 0) thirdVol -= 0.1;
            Stubborn_3->setVolume(thirdVol);

            myTime->startTime =clock();
        }
    }
   else if (zCount >= 3 )
    {
        if(clock() - myTime->startTime>15)
        {
            if(firstVol != 0) firstVol -= 0.1;
            Stubborn_1->setVolume(firstVol);

            if(secondVol != 0) secondVol -= 0.1;
            Stubborn_2->setVolume(secondVol);

            if(thirdVol != 1) thirdVol += 0.1;
            Stubborn_3->setVolume(thirdVol);

            myTime->startTime =clock();
        }
    }
}

void GLSounds::fourthGameSound(int)
{
    //TODO: ADD FOURTH SOUND
}
//TODO: maybe add a shop sound? it'd be funny if we just got a Kevin Macleod song in
void GLSounds::stopGameSound()
{
    Genesis_1->setIsPaused(true);
    Genesis_2->setIsPaused(true);
    Genesis_3->setIsPaused(true);
    Exposure_1->setIsPaused(true);
    Exposure_2->setIsPaused(true);
    Exposure_3->setIsPaused(true);
    Stubborn_1->setIsPaused(true);
    Stubborn_2->setIsPaused(true);
    Stubborn_3->setIsPaused(true);


    Genesis_1->setPlayPosition(0);
    Genesis_2->setPlayPosition(0);
    Genesis_3->setPlayPosition(0);
    Exposure_1->setPlayPosition(0);
    Exposure_2->setPlayPosition(0);
    Exposure_3->setPlayPosition(0);
    Stubborn_1->setPlayPosition(0);
    Stubborn_2->setPlayPosition(0);
    Stubborn_3->setPlayPosition(0);
}
void GLSounds::playSelectSoundOne()
{
    engine->play2D("sounds/Menu/Select1.wav", false, false, true)->setVolume(0.3);
}
void GLSounds::playSelectSoundTwo()
{
    engine->play2D("sounds/Menu/Select2.wav", false, false, true)->setVolume(0.3);
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
    firstVol = 0;
    secondVol = 0;
    thirdVol = 0;
    introMenu = engine->play2D("sounds/Menu/BeginningIntro.wav", false, true, true);
    mainMenu = engine->play2D("sounds/Menu/MenuLoop.wav", true, true, true);
    Genesis_1 = engine->play2D("sounds/Game/lvl1/Empty.wav", true, true, true);
    Genesis_2 = engine->play2D("sounds/Game/lvl1/Active.wav", true, true, true);
    Genesis_3 = engine->play2D("sounds/Game/lvl1/Main.wav", true, true, true);
    Exposure_1 = engine->play2D("sounds/Game/lvl2/Exposure-TITTGLoop.wav", true, true, true);
    Exposure_2 = engine->play2D("sounds/Game/lvl2/Exposure-2nd.wav", true, true, true);
    Exposure_3 = engine->play2D("sounds/Game/lvl2/Exposure-Full.wav", true, true, true);
    Stubborn_1 = engine->play2D("sounds/Game/lvl3/Stubborn-1.wav", true, true, true);
    Stubborn_2 = engine->play2D("sounds/Game/lvl3/Stubborn-2.wav", true, true, true);
    Stubborn_3 = engine->play2D("sounds/Game/lvl3/Stubborn-3.wav", true, true, true);

    if(introMenu) introMenu->setVolume(1);
    if(mainMenu) mainMenu->setVolume(1);
    if(Genesis_1) Genesis_1->setVolume(0);
    if(Genesis_2) Genesis_2->setVolume(secondVol);
    if(Genesis_3) Genesis_3->setVolume(thirdVol);
    if(Exposure_1) Exposure_1->setVolume(0);
    if(Exposure_2) Exposure_2->setVolume(secondVol);
    if(Exposure_3) Exposure_3->setVolume(thirdVol);
    if(Stubborn_1) Stubborn_1->setVolume(0);
    if(Stubborn_2) Stubborn_2->setVolume(secondVol);
    if(Stubborn_3) Stubborn_3->setVolume(thirdVol);

    return 1;
}
