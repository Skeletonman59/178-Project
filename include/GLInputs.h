#ifndef GLINPUTS_H
#define GLINPUTS_H
#include<Screen.h>
#include<Object.h>
#include<common.h>
#include<GLPlayer.h>
#include<GLSounds.h>
#include<GLProjectile.h>

class GLInputs
{
    public:
        GLInputs();
        GLTimer *myTime = new GLTimer();
        virtual ~GLInputs();

        void keyPress(Screen*, Screen*, Screen*, Screen*, Screen*, Object*, Object*, Object*, GLPlayer*, GLSounds*);            // when key pressed
        void keyPress2(GLPlayer*, Object*);
        void soundIterator(int&); //DEBUGGING: DELETE WHEN DONE
        void keyTest(Object*);   //keyPress/KeyUP cluttered, delete this when done
        void keyUP(Screen*, Screen*, Screen*, Screen*, Screen*, Screen*, GLPlayer*, Object*, Object*, Object*, Object*, GLSounds*);                               // when key released
        void keyBackground(float);    // parallax model & speed


        void mouseEventDown(Screen*, Screen* , Screen* , Screen*, Object*, Object*, Object*, GLTimer*, double, double); // mouse btn pressed
        void mouseEventUp(Screen*, Screen*,Screen*,Screen*,Screen*, GLPlayer*, Object*,Object*,Object*, GLTimer*, double, double);                                // mouse btn released
        void mouseWheel(double);              // mouse wheel rolled
        void mouseMove(float, float, float, float, Object*, Object*, Object*, double,double);       // mouse moved

        double prev_MouseX;      // current mouse location X before action
        double prev_MouseY;      // current mouse location Y before action

        bool mouse_Translate;    // if mouse moved
        bool mouse_Rotate;       // if mouse moved for rotation

        enum {LOADING, MENUSCREEN, HELPSCREEN, GAMESCREEN, PAUSESCREEN, PAUSEHELPSCREEN, CREDITSCREEN};  // For inputs, determines if button locations should be interactable
        enum {NEW_BUTTON, HELP_BUTTON, QUIT_BUTTON};
        int buttonToggle;       // Flag for key inputs
        int screenToggle;
        bool helpTransitioning; // Flag to control Help screen animation
        bool menuTransitioning; // to control screen animation

        WPARAM wParam;           // catching input interrupts

    protected:

    private:
};

#endif // GLINPUTS_H
