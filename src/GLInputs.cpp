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
void GLInputs::keyPress2(GLPlayer* pl)
{
    switch(wParam)
    {
    case VK_LEFT:
        pl->actionTrigger = pl->WALKLEFT;
        break;
    case VK_RIGHT:
        pl->actionTrigger = pl->WALKRIGHT;
        break;
    case VK_UP:
        pl->actionTrigger = pl->JUMP;
        break;
        case VK_SPACE:
        pl->actionTrigger = pl->ROLL;
        break;
    }
}

void GLInputs::keyPress(Screen* load, Screen* menu, Screen* help, Screen* game, Screen* pause, Object* newgame, Object* guide, Object* quit, GLPlayer* player)
{
    switch(wParam)
    {
    case VK_LEFT:
        if(screenToggle== GAMESCREEN)player->actionTrigger= player->WALKLEFT;
        break;
    case VK_RIGHT:
         if(screenToggle== GAMESCREEN)player->actionTrigger= player->WALKRIGHT;
        break;
    case VK_DOWN:
        switch(screenToggle) //WHERE ARE WE?
        {
        case LOADING:
            break;
        case PAUSESCREEN:
            switch(buttonToggle)
            {
            case NEW_BUTTON:
                newgame->moveTrigger = newgame->RETREAT;
                guide->moveTrigger = guide->POP;
                quit->moveTrigger = guide->RETREAT;
                buttonToggle = HELP_BUTTON;
                //cout << "new goes to help" << endl;
                break;
            case HELP_BUTTON:
                newgame->moveTrigger = newgame->RETREAT;
                guide->moveTrigger = guide->RETREAT;
                quit->moveTrigger = guide->POP;
                buttonToggle = QUIT_BUTTON;
                //cout << "help goes to quit" << endl;
                break;
            case QUIT_BUTTON:
                newgame->moveTrigger = newgame->POP;
                guide->moveTrigger = guide->RETREAT;
                quit->moveTrigger = guide->RETREAT;
                buttonToggle = NEW_BUTTON;
                //cout << "quit goes to new" << endl;
                break;
            default:
                newgame->moveTrigger = newgame->RETREAT;
                guide->moveTrigger = guide->RETREAT;
                quit->moveTrigger = guide->RETREAT;
                buttonToggle = NEW_BUTTON;
                break;
            }
            break;
        case MENUSCREEN:
            switch(buttonToggle)
            {
            case NEW_BUTTON:
                newgame->moveTrigger = newgame->RETREAT;
                guide->moveTrigger = guide->POP;
                quit->moveTrigger = guide->RETREAT;
                buttonToggle = HELP_BUTTON;
                //cout << "new goes to help" << endl;
                break;
            case HELP_BUTTON:
                newgame->moveTrigger = newgame->RETREAT;
                guide->moveTrigger = guide->RETREAT;
                quit->moveTrigger = guide->POP;
                buttonToggle = QUIT_BUTTON;
                //cout << "help goes to quit" << endl;
                break;
            case QUIT_BUTTON:
                newgame->moveTrigger = newgame->POP;
                guide->moveTrigger = guide->RETREAT;
                quit->moveTrigger = guide->RETREAT;
                buttonToggle = NEW_BUTTON;
                //cout << "quit goes to new" << endl;
                break;
            default:
                newgame->moveTrigger = newgame->RETREAT;
                guide->moveTrigger = guide->RETREAT;
                quit->moveTrigger = guide->RETREAT;
                buttonToggle = NEW_BUTTON;
                break;
            }
            break;
        case HELPSCREEN:
            break;
        case GAMESCREEN:
            break;
        }
        break;
    case VK_UP:
        switch(screenToggle) //WHERE ARE WE?
        {
        case LOADING:
            break;
        case PAUSESCREEN:
            //make menus button-interactable
            //if no button currently selected (start) select Quit
            //if selected button is New Game, make selected button be Quit
            //if selected button is Help, make selected button be New Game
            //if selected button is Quit, cycle up to Help
            switch(buttonToggle)
            {
            case NEW_BUTTON:
                newgame->moveTrigger = newgame->RETREAT;
                guide->moveTrigger = guide->RETREAT;
                quit->moveTrigger = guide->POP;
                buttonToggle = QUIT_BUTTON;
                //cout << "new goes to quit" << endl;
                break;
            case HELP_BUTTON:
                newgame->moveTrigger = newgame->POP;
                guide->moveTrigger = guide->RETREAT;
                quit->moveTrigger = guide->RETREAT;
                buttonToggle = NEW_BUTTON;
                //cout << "help goes to new" << endl;
                break;
            case QUIT_BUTTON:
                newgame->moveTrigger = newgame->RETREAT;
                guide->moveTrigger = guide->POP;
                quit->moveTrigger = guide->RETREAT;
                buttonToggle = HELP_BUTTON;
                //cout << "quit goes to help" << endl;
                break;
            default:
                newgame->moveTrigger = newgame->RETREAT;
                guide->moveTrigger = guide->RETREAT;
                quit->moveTrigger = guide->RETREAT;
                buttonToggle = QUIT_BUTTON;
                break;
            }
            break;
        case MENUSCREEN:
            switch(buttonToggle)
            {
            case NEW_BUTTON:
                newgame->moveTrigger = newgame->RETREAT;
                guide->moveTrigger = guide->RETREAT;
                quit->moveTrigger = guide->POP;
                buttonToggle = QUIT_BUTTON;
                //cout << "new goes to quit" << endl;
                break;
            case HELP_BUTTON:
                newgame->moveTrigger = newgame->POP;
                guide->moveTrigger = guide->RETREAT;
                quit->moveTrigger = guide->RETREAT;
                buttonToggle = NEW_BUTTON;
                //cout << "help goes to new" << endl;
                break;
            case QUIT_BUTTON:
                newgame->moveTrigger = newgame->RETREAT;
                guide->moveTrigger = guide->POP;
                quit->moveTrigger = guide->RETREAT;
                buttonToggle = HELP_BUTTON;
                //cout << "quit goes to help" << endl;
                break;
            default:
                newgame->moveTrigger = newgame->RETREAT;
                guide->moveTrigger = guide->RETREAT;
                quit->moveTrigger = guide->RETREAT;
                buttonToggle = QUIT_BUTTON;
                break;
            }
            break;
        case HELPSCREEN:
            break;
        case GAMESCREEN:
            break;
        }
        break;

    case VK_RETURN:
        switch(screenToggle) //WHERE ARE WE?
        {
        case LOADING:
            load->screenTrigger = load->FADEOUT;
            break;
        case MENUSCREEN:
            /*
            switch(buttonToggle)
            {
            case NEW_BUTTON:
                pause->current=false;
                newgame->moveTrigger = newgame->DISAPPEAR;
                guide->moveTrigger = guide->DISAPPEAR;
                quit->moveTrigger = quit->DISAPPEAR;
                screenToggle = GAMESCREEN;
               break;

            case HELP_BUTTON:
                 help->current= true;
                menu->current= false;
                newgame->moveTrigger = newgame->DISAPPEAR;
                guide->moveTrigger = guide->DISAPPEAR;
                quit->moveTrigger = quit->DISAPPEAR;
                screenToggle = HELPSCREEN;
                break;
            }
            */
            break;
        case HELPSCREEN:
            //go back
            help->screenTrigger = help->HELPOUT;
            /*
            help->current= false;
           menu->current= true;
            newgame->moveTrigger = newgame->APPEAR;
            guide->moveTrigger = guide->APPEAR;
            quit->moveTrigger = quit->APPEAR;
            creenToggle= MENUSCREEN;
            */
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

            //help->current= false;
            //menu->current= true;
            //screenToggle= MENUSCREEN;

            break;
        case GAMESCREEN:
            /*
            if (MessageBox(NULL,"Leave to main screen?", "Everything not saved will be lost ~Nintendo",MB_YESNO|MB_ICONQUESTION)==IDYES)
            {
                //make them go to main screen
                screenToggle = MENUSCREEN;
                newgame->moveTrigger = newgame->APPEAR;
                guide->moveTrigger = guide->APPEAR;
                quit->moveTrigger = quit->APPEAR;

                pause->current= true;
                player->playerSpawn= false;
                game->current=false;
                screenToggle = PAUSESCREEN;
                */
                newgame->moveTrigger = newgame->APPEAR;
                guide->moveTrigger = guide->APPEAR;
                quit->moveTrigger = quit->APPEAR;

                pause->current= true;
                player->playerSpawn= false;
                game->current=false;
                screenToggle = PAUSESCREEN;
            break;
        }
        break;
    }
}

void GLInputs::keyUP(Screen* load, Screen* help, Screen* menu, Screen* game, Screen* pause, Screen* credit, GLPlayer* player, Object* newgame, Object* guide, Object* quit)
{
    switch(wParam)
    {
    case VK_NUMPAD0:
        switch(screenToggle)
        {
        case MENUSCREEN:
            menu->current= false;
            credit->current= true;
            newgame->moveTrigger = newgame->DISAPPEAR;
            guide->moveTrigger = guide->DISAPPEAR;
            quit->moveTrigger = quit->DISAPPEAR;
            screenToggle = CREDITSCREEN;
            break;
        }
        break;
    case VK_RETURN:
        switch(screenToggle) //WHERE ARE WE?
        {
        case LOADING:
            //make menu move forward
            //make menu fade in
            menu->current= true;
           load->current= false;

            load->screenTrigger = load->NOTHING;
            menu->screenTrigger = menu->FADEIN;

            newgame->moveTrigger = newgame->APPEAR;
            guide->moveTrigger = guide->APPEAR;
            quit->moveTrigger = quit->APPEAR;

            screenToggle = MENUSCREEN;
            break;
        case MENUSCREEN:
            switch(buttonToggle)
            {
            case NEW_BUTTON:
                //TODO: activate game stuff
                //pause->current=false;
                newgame->moveTrigger = newgame->DISAPPEAR;
                guide->moveTrigger = guide->DISAPPEAR;
                quit->moveTrigger = quit->DISAPPEAR;
                screenToggle = GAMESCREEN;
               break;

                break;
            case HELP_BUTTON:
                help->screenTrigger = help->HELPIN;
                newgame->moveTrigger = newgame->DISAPPEAR;
                guide->moveTrigger = guide->DISAPPEAR;
                quit->moveTrigger = quit->DISAPPEAR;
                screenToggle = HELPSCREEN;
                break;
            case QUIT_BUTTON:
                if (MessageBox(NULL,"Are you sure you want to quit?", "EXIT GAME?",MB_YESNO|MB_ICONQUESTION)==IDYES)exit(0);
                break;
            default:
                break;
            }
            break;
        case HELPSCREEN:
            newgame->moveTrigger = newgame->APPEAR;
            guide->moveTrigger = guide->APPEAR;
            quit->moveTrigger = quit->APPEAR;

            screenToggle = MENUSCREEN;
            break;
        case CREDITSCREEN:
            credit->current= false;
            menu->current= true;
               newgame->moveTrigger = newgame->APPEAR;
                guide->moveTrigger = guide->APPEAR;
                quit->moveTrigger = quit->APPEAR;
            screenToggle=MENUSCREEN;
            break;
        case GAMESCREEN:
            game->current= true;
                player->playerSpawn = true;
                menu->current=false;
                screenToggle=GAMESCREEN;
            break;
        case PAUSESCREEN:
            switch(buttonToggle)
            {
            case NEW_BUTTON:
                // game->screenTrigger = game->HELPIN;
                game->current=true;
                player->playerSpawn = true;
                pause->current=false;

                newgame->moveTrigger = newgame->DISAPPEAR;
                guide->moveTrigger = guide->DISAPPEAR;
                quit->moveTrigger = quit->DISAPPEAR;
                screenToggle = GAMESCREEN;
                break;
            case HELP_BUTTON:
                help->current= true;
                menu->current= false;
                newgame->moveTrigger = newgame->DISAPPEAR;
                guide->moveTrigger = guide->DISAPPEAR;
                quit->moveTrigger = quit->DISAPPEAR;
                screenToggle = HELPSCREEN;

            case QUIT_BUTTON:
                menu->screenTrigger = menu->HELPIN;
                // pause->screenTrigger= pause->HELPOUT;
                game->current= false;
                player->playerSpawn = false;
                pause->current=false;
                menu->current= true;
                screenToggle = MENUSCREEN;
                break;
            }
            break;
        }
        break;
        default:
            player->actionTrigger= player->STAND;
        break;
    }
}

void GLInputs::mouseEventDown(Screen* load, Screen* menu, Screen* help, Object* newgame, Object* guide, Object* quit, GLTimer* T, double x, double y)
{
    prev_MouseX = x;    //keep previous x and y values
    prev_MouseY = y;

    switch (wParam)
    {
    case MK_LBUTTON:  //left mouse click
        switch(screenToggle)  //what screen are we on?
        {
        case LOADING:
            load->screenTrigger = load->FADEOUT;
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
                    //help->screenTrigger = help->HELPIN;
                }
                else if (y >= quit->normalizedBTL && y <= quit->normalizedBBL)
                {
                    //if (MessageBox(NULL,"Are you sure you want to quit?", "EXIT GAME?",MB_YESNO|MB_ICONQUESTION)==IDYES)exit(0);
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

void GLInputs::mouseEventUp(Screen* load, Screen* menu, Screen* help, Object* newgame, Object* guide, Object* quit, GLTimer* T, double x, double y)
{
    mouse_Rotate =false;    // reset rotation flag
    mouse_Translate =false; //reset translation flag
    switch (wParam)
    {
    case MK_LBUTTON:
        switch(screenToggle)
        {
        case LOADING:
            load->screenTrigger = load->NOTHING;
            menu->screenTrigger = menu->FADEIN;

            newgame->moveTrigger = newgame->APPEAR;
            guide->moveTrigger = guide->APPEAR;
            quit->moveTrigger = quit->APPEAR;

            screenToggle = MENUSCREEN;
            break;
        case MENUSCREEN:
            //make buttons go away
            //TODO: check if the button was originally pressed
            //Possible fix: check bool if both mousepress and mouserelease are in the same area?
            if(x >= 0 && x <= newgame->normalizedBRL)
            {
                if (y >= newgame->normalizedBTL && y <= newgame->normalizedBBL)
                {
                    //TODO: activate game stuff
                }
                else if (y >= guide->normalizedBTL && y <= guide->normalizedBBL)
                {
                    help->screenTrigger = help->HELPIN;
                    newgame->moveTrigger = newgame->DISAPPEAR;
                    guide->moveTrigger = guide->DISAPPEAR;
                    quit->moveTrigger = quit->DISAPPEAR;
                    screenToggle = HELPSCREEN;
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
