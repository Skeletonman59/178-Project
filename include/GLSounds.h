#ifndef GLSOUNDS_H
#define GLSOUNDS_H

#include<common.h>

class GLSounds
{
    public:
        GLSounds();
        GLTimer *myTime = new GLTimer();
        virtual ~GLSounds();

        ISoundEngine *engine = createIrrKlangDevice();
        ISound* introMenu;
        ISound* mainMenu;
        ISound* Genesis_1;
        ISound* Genesis_2;
        ISound* Genesis_3;
        ISound* Exposure_1;
        ISound* Exposure_2;
        ISound* Exposure_3;
        ISound* Stubborn_1;
        ISound* Stubborn_2;
        ISound* Stubborn_3;
        ISound* Funk_4;

        void playMenu();
        void stopMenu();
        void firstGameSound(int);
        void secondGameSound(int);
        void thirdGameSound(int);
        void fourthGameSound(int);
        void stopGameSound();
        void playSelectSoundOne();
        void playSelectSoundTwo();
        void pauseSound(char*);
        int initSounds();

        float firstVol;
        float secondVol;
        float thirdVol;

    protected:

    private:
};

#endif // GLSOUNDS_H
