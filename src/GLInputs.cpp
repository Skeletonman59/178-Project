#include "GLInputs.h"
#include <common.h>

GLInputs::GLInputs()
{
    //ctor

    prev_MouseX =0;     // init mouse values
    prev_MouseY =0;

    mouse_Translate =0;
    mouse_Rotate =0;

    firstReturn = false;
    helpTransitioning = false; // Flag to control Help screen animation
    menuTransitioning = false;
    arrowOscillate = false;
    bgSummon = false;
    gameToMenu = false;

    screenToggle = LOADING;
    myTime->startTime = clock();

}

GLInputs::~GLInputs()
{
    //dtor
}

void GLInputs::keyPress(Screen* screen, Menu* menu)
{
    switch(wParam)
    {
    case VK_LEFT:
        //pl->actionTrigger= pl->WALKLEFT;
        break;

    case VK_RIGHT:
        //pl->actionTrigger = pl->WALKRIGHT;
        break;

    case VK_DOWN:
        break;

    case VK_UP:
        break;

    case VK_ADD:
        break;
    case VK_SUBTRACT:
        break;
    case VK_RETURN:
        //screen->blackFade(0.125);
        //menu->fadeIn(0.125);
        //if((clock() - myTime->startTime) > 30)
        //{
        switch(screenToggle) //WHERE ARE WE?
        {
        case LOADING:        //LOADING: PRESS START, AFTERWARDS WE NEVER COME HERE AGAIN
            firstReturn = true;
            screenToggle = MENUSCREEN;
            break;
        case MENUSCREEN:
            break;
        case HELPSCREEN:
            //go back
            menuTransitioning = true;
            screenToggle = MENUSCREEN;
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
            menuTransitioning = true;
            screenToggle = MENUSCREEN;
            break;
        case GAMESCREEN:
             if (MessageBox(NULL,"Leave to main menu?", "Everything not saved will be lost ~Nintendo",MB_YESNO|MB_ICONQUESTION)==IDYES)
             {
                 //make them go to main menu
                 gameToMenu = true;
                 screenToggle = MENUSCREEN;
                 //exit(0); //TEMP
             }
            break;
        }
        break;
    }
}

void GLInputs::keyUP()
{
    switch(wParam)
    {
    default:
        break;
    }
}

void GLInputs::mouseEventDown(Menu* menu, Screen* help, Object* arrow, GLTimer* T, double x, double y)
{
    prev_MouseX = x;    //keep previous x and y values
    prev_MouseY = y;

    switch (wParam)
    {
    case MK_LBUTTON:
        //ON MOUSE CLICK:
        //keep the menu enum value saved. For example, if "HELP" is selected,
        //then ofc the Help screen shows up, but pressing [ESC] still has to
        //take you back to the main menu.

        //UPDATE: escape already closes the game, figure out how to stop that
        switch(screenToggle)
        {
        case LOADING:
            //do nothing, or open menu on mouseclick, TBD
            //if i DO decide to do on mouseclick, change firstReturn val
            firstReturn = true;
            screenToggle = MENUSCREEN;
            break;
        case MENUSCREEN:
            if (x >= menu->BUTTON_LEFT_LIMIT && x <= menu->BUTTON_RIGHT_LIMIT)
            {
                if      (y >= menu->NEW_GAME_Y1 && y <= menu->NEW_GAME_Y2)
                {
                    // Execute "New Game" action
                    //TODO: actually make a game. Something simple, a giant monster in a background
                    //trying to crush the player with his fists
                    //considering background in BAMF - pegboard nerds
                    //or https://www.freepik.com/premium-ai-image/man-stands-front-city-with-giant-monster-background_46188508.htm

                    //edited the second image, i can probably try to make the alpha dimmer to make the monster pop out less
                    bgSummon = true;
                    screenToggle = GAMESCREEN;

                }
                else if (y >= menu->HELP_Y1 && y <= menu->HELP_Y2)           // Execute "Help" action
                {
                    helpTransitioning = true;
                    arrow->objPosition.y = 1.5;
                    screenToggle = HELPSCREEN;
                }
                else if (y >= menu->QUIT_Y1 && y <= menu->QUIT_Y2)
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

void GLInputs::mouseEventUp()
{
    mouse_Rotate =false;    // reset rotation flag
    mouse_Translate =false; //reset translation flag
}

void GLInputs::mouseWheel(double delta)
{

}

void GLInputs::mouseMove(Menu* menu, Screen* help, Object* arrow, double x, double y)
{
    //prev_MouseX =x;                      // update previous mouse x
    //prev_MouseY =y;
    //here in the mousemove function, we will check if the mouse is touching a button, which will make
    //the hitbox glow
    //cout << x << " " << y << endl;
    //cout << menu->buttonToggle << endl;
    switch (screenToggle)
    {
    case LOADING:
        break;

    case MENUSCREEN:
        if (x >= menu->BUTTON_LEFT_LIMIT && x <= menu->BUTTON_RIGHT_LIMIT)
        {
            if (y >= menu->NEW_GAME_Y1 && y <= menu->NEW_GAME_Y2)
            {
                //Trigger "New Game"
                menu->buttonToggle = menu->NEW;
                if(!menuTransitioning&& !helpTransitioning && firstReturn && !gameToMenu)arrowOscillate = true;
                arrow->objPosition.y = -0.2;

            }
            else if (y >= menu->HELP_Y1 && y <= menu->HELP_Y2)
            {
                // Trigger "Help"
                menu->buttonToggle = menu->HELP;
                if(!menuTransitioning && !helpTransitioning && firstReturn && !gameToMenu)arrowOscillate = true;
                arrow->objPosition.y = -0.4;
            }
            else if (y >= menu->QUIT_Y1 && y <= menu->QUIT_Y2)
            {
                //Trigger "Quit"
                menu->buttonToggle = menu->QUIT;
                if(!menuTransitioning&& !helpTransitioning && firstReturn && !gameToMenu)arrowOscillate = true;
                arrow->objPosition.y = -0.6;

            }
            else  //no button is hovered
            {
                arrow->objPosition.y = 1.5; //lazy way to get arrow out of screen
                arrowOscillate = false;
                menu->buttonToggle = menu->NONE;
            }
        }
        else arrowOscillate = false;
        break;
    case HELPSCREEN:
        break;
    case GAMESCREEN:
        break;
    }

}
void GLInputs::keyBackground(GLParallax* prlx, float speed)
{
    //  if(clock() - myTime->startTime>15)
    switch(wParam)
    {
    case VK_UP:               // move parallax up
        prlx->yMin -=speed;
        prlx->yMax -=speed;
        break;

    case VK_DOWN:           // move parallax down
        prlx->yMin +=speed;
        prlx->yMax +=speed;
        break;

    case VK_LEFT:            // move parallax left

        prlx->xMin -=speed;
        prlx->xMax -=speed;
        break;

    case VK_RIGHT:         //// move parallax right

        prlx->xMin +=speed;
        prlx->xMax +=speed;
        break;
        //    myTime->startTime =clock();
    }
}
