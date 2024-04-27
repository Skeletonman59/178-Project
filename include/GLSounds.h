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
        ISound* Empty_1;
        ISound* Active_1;
        ISound* Main_1;
        ISound* TITT_2;
        ISound* Second_2;
        ISound* Full_2;


        void playMenu();
        void stopMenu();
        void playGameSound();
        void playSound(char *);
        void pauseSound(char *);
        int initSounds();

// NOTE (Skele#1#): GAME_ITERATOR is used to test game audio looping. It is meant to be replaced with other factors, such as what level we are on, and how many enemies are on the screen OR the player has killed.
        int GAME_ITERATOR;
        float ActVol;
        float MenuVol;

    protected:

    private:
};

#endif // GLSOUNDS_H
