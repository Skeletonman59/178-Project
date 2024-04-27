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
        void playMenu();
        void stopMenu();
        void playSound(char *);
        void pauseSound(char *);
        int initSounds();

    protected:

    private:
};

#endif // GLSOUNDS_H
