#include "Object.h"

Object::Object()
{
    //ctor
    vert[0].x =-0.5; vert[0].y = -0.5; vert[0].z =-1.0;
    vert[1].x = 0.5; vert[1].y = -0.5; vert[1].z =-1.0;
    vert[2].x = 0.5; vert[2].y =  0.5; vert[2].z =-1.0;
    vert[3].x =-0.5; vert[3].y =  0.5; vert[3].z =-1.0;
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
void Object::actions()
{
    cout << objPosition.x << endl;
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
    default:
        break;
    }
}
