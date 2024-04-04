#include "GLInputs.h"
#include <common.h>

GLInputs::GLInputs()
{
    //ctor

    prev_MouseX =0;     // init mouse values
    prev_MouseY =0;

    mouse_Translate =0;
    mouse_Rotate =0;

    helpTransitioning = false; // Flag to control Help screen animation
    menuTransitioning = false;

    screenToggle = LOADING;
    myTime->startTime = clock();
}

GLInputs::~GLInputs()
{
    //dtor
}

void GLInputs::keyPress(Screen* load, Screen* menu, Screen* help)
{
    switch(wParam)
    {
    case VK_LEFT:
        break;
    case VK_RIGHT:
        break;
    case VK_DOWN:
        break;
    case VK_UP:
        break;

    case VK_RETURN:
        switch(screenToggle) //WHERE ARE WE?
        {
        case LOADING:
            load->screenTrigger = load->FADEOUT;
            break;
        case MENUSCREEN:
            break;
        case HELPSCREEN:
            //go back
            help->screenTrigger = help->HELPOUT;
            break;
        case GAMESCREEN:
            break;
        }
    case VK_ESCAPE:
        switch(screenToggle) //WHERE ARE WE?
        {
        case LOADING:
            break;
        case MENUSCREEN:
            //broken if quits
            break;
        case HELPSCREEN:  //escape also should escape from help
            //go back
            help->screenTrigger = help->HELPOUT;
            break;
        case GAMESCREEN:
            if (MessageBox(NULL,"Leave to main screen?", "Everything not saved will be lost ~Nintendo",MB_YESNO|MB_ICONQUESTION)==IDYES)
            {
                //make them go to main screen
                screenToggle = MENUSCREEN;
                //exit(0); //TEMP
            }
            break;
        }
        break;
    }
}

void GLInputs::keyUP(Screen* load, Screen* menu, Object* newgame, Object* guide, Object* quit)
{
    switch(wParam)
    {
    case VK_RETURN:
        switch(screenToggle) //WHERE ARE WE?
        {
        case LOADING:
            //make menu move forward
            //make menu fade in
            load->screenTrigger = load->NOTHING;
            menu->screenTrigger = menu->FADEIN;

            newgame->moveTrigger = newgame->APPEAR;
            guide->moveTrigger = guide->APPEAR;
            quit->moveTrigger = quit->APPEAR;

            screenToggle = MENUSCREEN;
            break;
        case MENUSCREEN:
            break;
        case HELPSCREEN:
            newgame->moveTrigger = newgame->APPEAR;
            guide->moveTrigger = guide->APPEAR;
            quit->moveTrigger = quit->APPEAR;

            screenToggle = MENUSCREEN;
            break;
        case GAMESCREEN:
            break;
        }
        break;
    default:
        break;
    }
}

void GLInputs::mouseEventDown(Screen* menu, Screen* help, Object* newgame, Object* guide, Object* quit, GLTimer* T, double x, double y)
{
    prev_MouseX = x;    //keep previous x and y values
    prev_MouseY = y;

    switch (wParam)
    {
    case MK_LBUTTON:
        switch(screenToggle)
        {
        case LOADING:
            break;
        case MENUSCREEN:

            if(x >= 0 && x <= newgame->normalizedBRL)
            {
                if (y >= newgame->normalizedBTL && y <= newgame->normalizedBBL)
                {
                    //TODO: activate game stuff
                }
                else if (y >= guide->normalizedBTL && y <= guide->normalizedBBL)
                {
                    help->screenTrigger = help->HELPIN;
                }
                else if (y >= quit->normalizedBTL && y <= quit->normalizedBBL)
                {
                    if (MessageBox(NULL,"Are you sure you want to quit?", "EXIT GAME?",MB_YESNO|MB_ICONQUESTION)==IDYES)exit(0);
                }
            }
            break;
        case HELPSCREEN:
            break;
        case GAMESCREEN:
            break;
        }

        break;
    case MK_RBUTTON:

        break;

    case MK_MBUTTON:
        // something you like to add
        break;

    default:
        break;
    }
}

void GLInputs::mouseEventUp(Object* newgame, Object* guide, Object* quit, GLTimer* T, double x, double y)
{
    mouse_Rotate =false;    // reset rotation flag
    mouse_Translate =false; //reset translation flag
    switch (wParam)
    {
    case MK_LBUTTON:
        switch(screenToggle)
        {
        case LOADING:
            break;
        case MENUSCREEN:
            //make buttons go away
            newgame->moveTrigger = newgame->DISAPPEAR;
            guide->moveTrigger = guide->DISAPPEAR;
            quit->moveTrigger = quit->DISAPPEAR;
            screenToggle = HELPSCREEN;
            break;
        case HELPSCREEN:
            break;
        case GAMESCREEN:
            break;
        }

        break;
    case MK_RBUTTON:

        break;

    case MK_MBUTTON:
        // something you like to add
        break;

    default:
        break;
    }
}

void GLInputs::mouseWheel(double delta)
{

}
void GLInputs::mouseMove(float w, float h, float screenWidth, float screenHeight, Object* newgame, Object* guide, Object* quit, double x, double y)
{
    switch (screenToggle)
    {
    case LOADING:
        break;
    case MENUSCREEN:
        //What is this? Mouse coord normalize tester. divide a button limit by the screen's width/height
        //and then multiply by the resized value to get a semi-accurate coordinate.
        //why semi-accurate? mouse pos is in double, button coords are in floats.
        /*
                cout << "full width and height:  " << screenWidth << " " << screenHeight << endl;
                cout << "resized screen:         " << w << " " << h << endl;
                cout << "mouse coordinate:       " << (float)x << " " << (float)y << endl;
                cout << "Button limit:           " << normalizedBTL  << " " << normalizedBBL <<endl << endl;
        */

        if(x >= 0 && x <= newgame->normalizedBRL) //which BRL doesn't matter they're all the same
        {
            if (y >= newgame->normalizedBTL && y <= newgame->normalizedBBL) newgame->moveTrigger = newgame->POP;
            else if (y >= guide->normalizedBTL && y <= guide->normalizedBBL) guide->moveTrigger = guide->POP;
            else if (y >= quit->normalizedBTL && y <= quit->normalizedBBL) quit->moveTrigger = quit->POP;
            else
            {
                newgame->moveTrigger = newgame->RETREAT;
                guide->moveTrigger = guide->RETREAT;
                quit->moveTrigger = quit->RETREAT;
            }
        }
        else
        {
            newgame->moveTrigger = newgame->RETREAT;
            guide->moveTrigger = guide->RETREAT;
            quit->moveTrigger = quit->RETREAT;
        }
        break;
    case HELPSCREEN:
        break;
    case GAMESCREEN:
        break;
    }

}
void GLInputs::keyBackground(float speed)
{
    //  if(clock() - myTime->startTime>15)
    switch(wParam)
    {
    case VK_UP:               // move parallax up
        break;

    case VK_DOWN:           // move parallax down
        break;

    case VK_LEFT:            // move parallax left
        break;

    case VK_RIGHT:         //// move parallax right
        break;
        //    myTime->startTime =clock();
    }
}
