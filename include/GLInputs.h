#ifndef GLINPUTS_H
#define GLINPUTS_H
#include<GLParallax.h>
#include<GLPlayer.h>
#include<Screen.h>
#include<Menu.h>
#include<Object.h>
#include<common.h>

class GLInputs
{
    public:
        GLInputs();
        GLTimer *myTime = new GLTimer();
        virtual ~GLInputs();

        void keyPress(Screen*, Menu*);                // when key pressed
        void keyUP();               // when key released
        void keyBackground(GLParallax *, float);     // parallax model & speed


        void mouseEventDown(Menu*, Screen*, Object*, GLTimer*, double, double); // mouse btn pressed
        void mouseEventUp();                                // mouse btn released
        void mouseWheel(double);              // mouse wheel rolled
        void mouseMove(Menu*, Screen*, Object* arrow, double,double);       // mouse moved

        double prev_MouseX;      // current mouse location X before action
        double prev_MouseY;      // current mouse location Y before action

        bool mouse_Translate;    // if mouse moved
        bool mouse_Rotate;       // if mouse moved for rotation

        bool firstReturn;        //get out of screen

        enum {LOADING, MENUSCREEN, HELPSCREEN, GAMESCREEN};  // For inputs, determines if button locations should be interactable
        int screenToggle;
        bool helpTransitioning; // Flag to control Help screen animation
        bool menuTransitioning; // to control menu animation
        bool arrowOscillate;    // flag for arrow movement within menu
        bool bgSummon;
        bool gameToMenu;

        WPARAM wParam;           // catching input interrupts

    protected:

    private:
};

#endif // GLINPUTS_H
