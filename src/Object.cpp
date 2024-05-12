#include "Object.h"

Object::Object()
{
    //ctor
    vert[0].x =-0.5;
    vert[0].y = -0.5;
    vert[0].z =-1.0;
    vert[1].x = 0.5;
    vert[1].y = -0.5;
    vert[1].z =-1.0;
    vert[2].x = 0.5;
    vert[2].y =  0.5;
    vert[2].z =-1.0;
    vert[3].x =-0.5;
    vert[3].y =  0.5;
    vert[3].z =-1.0;
}

Object::~Object()
{
    //dtor
}
void Object::initObject(float x, float y, float z, int fX, int fY, char* fileName)
{
    objPosition.x = x;  //initialize position
    objPosition.y = y;  //out of screen until needed
    objPosition.z = z;

    objScale.x = 1.0;   //initialize scale
    objScale.y = 0.2;
    objScale.z = 1.5;

    framesX = fX;               // record number of frames
    framesY = fY;

    barTrigger = FULL;
    texture->loadTexture(fileName); //loading my background

    myTime->startTime = clock();
}

void Object::drawObject()
{
    glTranslatef(objPosition.x,objPosition.y,objPosition.z);
    glScalef(objScale.x,objScale.y,objScale.z);

    glColor3f(1.0,1.0,1.0);    //white rectangle
    texture->bindTexture();    //binding my background


    glBegin(GL_QUADS);
    glTexCoord2f(xMin,yMax);
    glVertex3f(vert[0].x,vert[0].y,vert[0].z);

    glTexCoord2f(xMax,yMax);
    glVertex3f(vert[1].x,vert[1].y,vert[1].z);

    glTexCoord2f(xMax,yMin);
    glVertex3f(vert[2].x,vert[2].y,vert[2].z);

    glTexCoord2f(xMin,yMin);
    glVertex3f(vert[3].x,vert[3].y,vert[3].z);

    glEnd();
}
void Object::default_obj()
{
    xMin = 0.0;
    xMax = 1.0;
    yMax = 1.0;
    yMin = 0.0;
}

void Object::new_button(float w, float h, float screenWidth, float screenHeight)
{
    xMin = 0;
    xMax = 1.0/(float)framesX;
    yMax = 1.0/(float)framesY;
    yMin = yMax-1.0/(float)framesY;

    BUTTON_RIGHT_LIMIT = 500;
    BUTTON_TOP_LIMIT = 265;
    BUTTON_BOTTOM_LIMIT = 365;

    normalizedBRL = (BUTTON_RIGHT_LIMIT / screenWidth)*w;
    normalizedBTL = (BUTTON_TOP_LIMIT / screenHeight)*h;
    normalizedBBL = (BUTTON_BOTTOM_LIMIT / screenHeight)*h;
}
void Object::continue_button(float w, float h, float screenWidth, float screenHeight)
{
    xMin = 0;
    xMax = 1.0/(float)framesX;
    yMax = 4.0/(float)framesY;
    yMin = yMax-1.0/(float)framesY;

    BUTTON_RIGHT_LIMIT = 500;
    BUTTON_TOP_LIMIT = 265;
    BUTTON_BOTTOM_LIMIT = 365;

    normalizedBRL = (BUTTON_RIGHT_LIMIT / screenWidth)*w;
    normalizedBTL = (BUTTON_TOP_LIMIT / screenHeight)*h;
    normalizedBBL = (BUTTON_BOTTOM_LIMIT / screenHeight)*h;
}


void Object::guide_button(float w, float h, float screenWidth, float screenHeight)
{
    xMin = 0;
    xMax = 1.0/(float)framesX;
    yMax = 2.0/(float)framesY;
    yMin = yMax-1.0/(float)framesY;

    BUTTON_RIGHT_LIMIT = 500;
    BUTTON_TOP_LIMIT = 385;
    BUTTON_BOTTOM_LIMIT = 480;

    normalizedBRL = (BUTTON_RIGHT_LIMIT / screenWidth)*w;
    normalizedBTL = (BUTTON_TOP_LIMIT / screenHeight)*h;
    normalizedBBL = (BUTTON_BOTTOM_LIMIT / screenHeight)*h;
}

void Object::quit_button(float w, float h, float screenWidth, float screenHeight)
{
    xMin = 0;
    xMax = 1.0/(float)framesX;
    yMax = 3.0/(float)framesY;
    yMin = yMax-1.0/(float)framesY;

    BUTTON_RIGHT_LIMIT = 500;
    BUTTON_TOP_LIMIT = 490;
    BUTTON_BOTTOM_LIMIT = 585;

    normalizedBRL = (BUTTON_RIGHT_LIMIT / screenWidth)*w;
    normalizedBTL = (BUTTON_TOP_LIMIT / screenHeight)*h;
    normalizedBBL = (BUTTON_BOTTOM_LIMIT / screenHeight)*h;
}
void Object::health_bar(float w, float h, float screenWidth, float screenHeight)
{
    xMin = 0;
    xMax = 1.0/(float)framesX;
    yMax = 1.0/(float)framesY;
    yMin = yMax-1.0/(float)framesY;
}
void Object::shop_obj()
{
    xMin =0;
    yMax =1.0/(float)framesY;
    xMax =1.0/(float)framesX;
    yMin =yMax-1.0/(float)framesY;

    objScale.x = 2.0;   //initialize scale
    objScale.y = 2.0;
    objScale.z = 1.0;
}

void Object::actions()
{
    //cout << objPosition.x << endl;
    switch (moveTrigger)
    {
    case APPEAR:
        if(clock() - myTime->startTime>30)
        {
            if (objPosition.x < -0.9) objPosition.x += 0.1;
            myTime->startTime = clock();
        }
        break;
    case POP:
        if(clock() - myTime->startTime>20)
        {
            if (objPosition.x < -0.7) objPosition.x += 0.1;
            myTime->startTime = clock();
        }
        break;
    case RETREAT:
        if(clock() - myTime->startTime>30)
        {
            if (objPosition.x > -0.8) objPosition.x -= 0.1;
            myTime->startTime = clock();
        }
        break;
    case DISAPPEAR:
        if(clock() - myTime->startTime>30)
        {
            if (objPosition.x > -2) objPosition.x -= 0.1;
            myTime->startTime = clock();
        }
        break;
    case ON:
        if(clock() - myTime->startTime>30)
        {
            if (objPosition.y  > 0.5) objPosition.x += 0.1;
            myTime->startTime = clock();
        }
        break;
    case OFF:
        objPosition.y = 1;
        break;
    case OPEN:
        if(clock() - myTime->startTime>300)
        {
            if(xMax < 4.0/framesX)
            {

                xMin +=1.0/framesX;
                xMax +=1.0/framesX;
            }
            myTime->startTime =clock();
        }
        break;
    case CLOSED:
        if(clock() - myTime->startTime>300)
        {
            if(xMax > 1.0/framesX)
            {

                xMin -=1.0/framesX;
                xMax -=1.0/framesX;
            }
            myTime->startTime =clock();
        }
        break;
    default:
        break;
    }
}
// TODO (Skele#5#): ADD HEALTH BAR SPRITE LOGIC, instead of pos changes, do position changes (xMax and all that)
void Object::barActions()
{
    switch (barTrigger)
    {
        //-0.6,0.5,0
        break;
    case FULL:
        xMin = 0;
        xMax = 1.0/(float)framesX;
        yMax = 1.0/(float)framesY;
        yMin = yMax-1.0/(float)framesY;
        break;
    case QUARTER:
        xMin = 0;
        xMax = 1.0/(float)framesX;
        yMax = 2.0/(float)framesY;
        yMin = yMax-1.0/(float)framesY;
        break;
    case THIRD:
        xMin = 0;
        xMax = 1.0/(float)framesX;
        yMax = 3.0/(float)framesY;
        yMin = yMax-1.0/(float)framesY;
        break;
    case DOUBLE:
        xMin = 0;
        xMax = 1.0/(float)framesX;
        yMax = 4.0/(float)framesY;
        yMin = yMax-1.0/(float)framesY;
        break;
    case SINGLE:
        xMin = 0;
        xMax = 1.0/(float)framesX;
        yMax = 5.0/(float)framesY;
        yMin = yMax-1.0/(float)framesY;
        break;
    case EMPTY:
        xMin = 0;
        xMax = 1.0/(float)framesX;
        yMax = 6.0/(float)framesY;
        yMin = yMax-1.0/(float)framesY;
        break;

    default:
        break;
    }
}

