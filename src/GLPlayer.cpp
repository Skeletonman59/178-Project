#include "GLPlayer.h"

GLPlayer::GLPlayer()
{
    //ctor
    vert[0].x = -0.5;
    vert[0].y = -0.5;
    vert[0].z =-1.0;
    vert[1].x = 0.5;
    vert[1].y = -0.5;
    vert[1].z =-1.0;
    vert[2].x = 0.5;
    vert[2].y = 0.5;
    vert[2].z =-1.0;
    vert[3].x = -0.5;
    vert[3].y = 0.5;
    vert[3].z =-1.0;
}

GLPlayer::~GLPlayer()
{
    //dtor
}
void GLPlayer::drawPlayer()
{
    glTranslatef(plPosition.x, plPosition.y, plPosition.z);
    glScalef(plScale.x, plScale.y, plScale.z);

    glColor3f(1.0,1.0,1.0);  //white rectangle
    texture->bindTexture(); //binding my background

    glBegin(GL_QUADS);

    glTexCoord2f(xMin, yMax);
    glVertex3f(vert[0].x, vert[0].y, vert[0].z);

    glTexCoord2f(xMax,yMax);
    glVertex3f(vert[1].x, vert[1].y, vert[1].z);

    glTexCoord2f(xMax,yMin);
    glVertex3f(vert[2].x, vert[2].y, vert[2].z);

    glTexCoord2f(xMin,yMin);
    glVertex3f(vert[3].x, vert[3].y, vert[3].z);
    glEnd();
}


bool GLPlayer::leftBound()        //check if player is hitting left wall
{
    return plPosition.x <= -5;

}
bool GLPlayer::rightBound()        // check if player is hitting right wall
{
    return plPosition.x >= 5;
}

void GLPlayer::initPlayer(int x, int y, char* fileName)
{
    plPosition.x =0;         // initialize positions
    plPosition.y =-1.5;
    plPosition.z = -6.0;

    plScale.x = 1.0;           // initialize scale
    plScale.y = 1.0;
    plScale.z = 1.0;

    framesX = x;               // record number of frames
    framesY = y;

    jumping = false;
    hp = 5;
    playeralive = true;
    shooting = false;
    hit = false;


    texture->loadTexture(fileName); //loading my background

    xMin =0;
    yMax =2.0/(float)framesY;
    xMax =1.0/(float)framesX;
    yMin =yMax-1.0/(float)framesY;

    actionTrigger=0;
    t = 0;
    vY = 30;
    myTime->startTime = clock();
}



void GLPlayer::actions()
{
    if((clock() - myTime->startTime) > 100)
    {
    	if(shooting)
		{
			if( rightBound())
            {
                actionTrigger = STAND;
            }
            else
            {
//FRAME DATA
                if(yMin >= 3.0f/framesY)
				{
					xMin = 1.0f/framesX;
					xMax = 2.0f/framesX;
					yMin = 2.0f/framesY;
					yMax = 3.0f/framesY;
					//shooting = false;
				}
				else
				{
					if(xMin >= 1.0f)
					{
						xMin = 0.0f;
						xMax = 1.0f/framesX;
						yMin += 1.0f/framesY;
						yMax += 1.0f/framesY;
					}
					else
					{
					xMin += 1.0f/framesX;
					xMax += 1.0f/framesX;
					}
				}
            }
		}
		else if(hit)
		{
			if(yMin >= 4.0f/framesY){
				hit = false;
				actionTrigger = STAND;
				direction = plScale.x;
			}
			else
			{
				if(xMin >= 1.0f)
				{
					xMin = 0.0f;
					xMax = 1.0f/framesX;
					yMin += 1.0f/framesY;
					yMax += 1.0f/framesY;
				}
				else
				{
					xMin += 1.0f/framesX;
					xMax += 1.0f/framesX;
				}
			}
			plPosition.x += 0.1f * direction;
		}
		else
		{
        switch(actionTrigger)
        {
        case STAND:

            xMin =1.0f/(float)framesX;
            xMax = 2.0/(float)framesX;

            yMax =3.0/(float)framesY;
            yMin =yMax-1.0/(float)framesY;

            break;

        case WALKLEFT:                   // position moving left & if left wall-> stop
            if( leftBound())
            {
                actionTrigger = STAND;
            }
            else
            {
                plScale.x = -1.0f;
                if(xMin >= 1.0f)
				{
					xMin = 0.0f;
					xMax = 1.0f/(float)framesX;
					yMin += 1.0f/(float)framesY;
					yMax += 1.0f/(float)framesY;
				}
				if(yMin >= 2.0f/(float)framesY && xMin >= 1.0f/framesX)
				{
					xMin = 0.0f;
					xMax = 1.0f/(float)framesX;
					yMin = 0.0f;
					yMax = 1.0f/framesY;
				}

                xMax += 1.0/(float)framesX;
                xMin += 1.0/(float)framesX;
                plPosition.x -=.1;
                direction = -1;
            }
            break;

        case WALKRIGHT:                 //position moving right & if right wall -> stop
            if( rightBound())
            {
                actionTrigger = STAND;
            }
            else
            {
                plScale.x = 1.0f;
                if(xMin >= 1.0f)
				{
					xMin = 0.0f;
					xMax = 1.0f/(float)framesX;
					yMin += 1.0f/(float)framesY;
					yMax += 1.0f/(float)framesY;
				}
				if(yMin >= 2.0f/(float)framesY && xMin >= 1.0f/framesX)
				{
					xMin = 0.0f;
					xMax = 1.0f/(float)framesX;
					yMin = 0.0f;
					yMax = 1.0f/framesY;
				}

                xMin+=1.0/(float)framesX;
                xMax+=1.0/(float)framesX;
                plPosition.x +=0.1;
                direction = 1;

            }
            break;

        case JUMP:
            jumping = true;
            break;
        case ROLL:                 //position moving right & if right wall -> stop
            if( rightBound())
            {
                actionTrigger = STAND;
            }
            else
            {
                //plScale.x = 0.3f;
                yMax=3.0/(float)framesY;
                yMin=yMax-1.0/(float)framesY;

                xMin+=1.0/(float)framesX;
                xMax+=1.0/(float)framesX;
                plPosition.x +=0.1;

            }
            break;

            myTime->startTime = clock();
        case SHOOT:                 //position moving right & if right wall -> stop
            if( rightBound())
            {
                actionTrigger = STAND;
            }
            else
            {
//FRAME DATA
                if(yMin >= 3.0f/framesY && xMin >= 1.0f/framesX)
				{
					actionTrigger = STAND;
					shooting = false;
				}
				else
				{
					if(xMin >= 1.0f)
					{
						xMin = 0.0f;
						xMax = 1.0f/framesX;
						yMin += 1.0f/framesY;
						yMax += 1.0f/framesY;
					}
					else
					{
					xMin += 1.0f/framesX;
					xMax += 1.0f/framesX;
					}
				}
            }
            break;

        default:
            break;
        }
		}
        //myTime->startTime = clock();
        if(jumping)
        {
            plPosition.y += (vY * t - 0.5 * GRAVITY * pow(t,2)) / 300;
            t += 0.4f;
            if(plPosition.y < -1.5f)
            {
                t = 0;
                actionTrigger = STAND;
                plPosition.y = -1.5f;
                jumping = false;
            }
        }
        myTime->startTime = clock();
    }
}
