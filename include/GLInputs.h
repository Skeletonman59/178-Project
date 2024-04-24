#ifndef GLINPUTS_H
#define GLINPUTS_H
#include<Screen.h>
#include<Object.h>
#include<common.h>
#include<GLPlayer.h>

class GLInputs
{
    public:
        GLInputs();
        GLTimer *myTime = new GLTimer();
        virtual ~GLInputs();

        void keyPress(Screen*, Screen*, Screen*, Screen*, Screen*, Object*, Object*, Object*, GLPlayer*);            // when key pressed
        void keyPress2(GLPlayer*);
        void keyUP(Screen*, Screen*, Screen*, Screen*, Screen*, Screen*, GLPlayer* player , Object*, Object*, Object*);                               // when key released
        void keyBackground(float);    // parallax model & speed


        void mouseEventDown(Screen*, Screen*, Screen*,Object*,Object*,Object*, GLTimer*, double, double); // mouse btn pressed
        void mouseEventUp(Screen*, Screen*,Screen*,Object*,Object*,Object*, GLTimer*, double, double);                                // mouse btn released
        void mouseWheel(double);              // mouse wheel rolled
        void mouseMove(float, float, float, float, Object*, Object*, Object*, double,double);       // mouse moved

        double prev_MouseX;      // current mouse location X before action
        double prev_MouseY;      // current mouse location Y before action

        bool mouse_Translate;    // if mouse moved
        bool mouse_Rotate;       // if mouse moved for rotation

        enum {LOADING, MENUSCREEN, HELPSCREEN, GAMESCREEN, PAUSESCREEN, CREDITSCREEN};  // For inputs, determines if button locations should be interactable
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
