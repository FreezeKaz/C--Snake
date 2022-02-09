#include <iostream>
#include "snake.hpp"


Snake::Snake(int length, int startDirection)
{   
    int x = SIZE/2;
    int y = SIZE/2;
    for(int i=0; i < length; i++)
    {
        switch (startDirection)
        {
        case 0:
        case 1:
            y += 1;
            break;
        case 2:
        case 3:
            x += 1;
            break;
        default:
            break;
        }
        grow(x,y,startDirection);
    }
    this->dir = startDirection;
    
}

Segment Snake::getHead()
{return *head;}

void Snake::move()
{
    delBack();
    growAtHead();
}

void Snake::turnSnake(int dir)
{
    head->setDir(dir);
}
void Snake::grow(int x, int y, int dir)
{
    Segment *newSegment = new Segment(x, y, 2);
    int xPos = x;
    int yPos = y;

    if (head == NULL)
    {
        head = newSegment;
        return;
    }
 
    newSegment->setX(xPos);
    newSegment->setY(yPos);
    newSegment->setDir(dir);
    newSegment->next = head;
    head = newSegment;

}

void Snake::growAtHead()
{
    
    int xPos = head->getX();
    int yPos = head->getY();

    if (head == NULL)
    {
 
        return;
    }

    switch (head->getDir())
    {
    case UP:
        yPos -= 1;
        break;
    case DOWN:
        yPos += 1;
        break;
    case RIGHT:
        xPos += 1;
        break;
    case LEFT:
        xPos -= 1;
        break;
    default:
        break;
    }

    Segment *newSegment = new Segment(xPos, yPos, dir);
    newSegment->setX(xPos);
    newSegment->setY(yPos);
    newSegment->setDir(head->getDir());
    newSegment->next = head;
    head = newSegment; 
}

void Snake::growBack()
{
    Segment *loop = head;

    while (loop->next != NULL)
    {
        loop = loop->next;
    }

    int xPos = loop->getX();
    int yPos = loop->getY();

    switch (loop->getDir())
    {
    case UP:
        yPos += 1;
        break;
    case DOWN:
        yPos -= 1;
        break;
    case RIGHT:
        xPos -= 1;
        break;
    case LEFT:
        xPos += 1;
        break;
    default:
        break;
    }

    Segment *newSegment  = new Segment(xPos, yPos, loop->getDir());
    newSegment->setY(yPos);
    newSegment->setDir(head->getDir());
    loop->next = newSegment;
}

void Snake::delBack()
{
    Segment *loop = head;
    Segment *last = NULL;
    if(head->next == NULL)
    {
        head = NULL;
    }
    else
    {
        while(loop->next->next != NULL)
        {
            loop = loop->next;
        }
        last = loop->next;
        loop->next = NULL;
        delete last;
    }
}

int R = 255;
int G = 0;
int B = 0;

void Snake::print(SDL_Renderer* renderer,bool rgb)
{
    Segment *loop = head;

    if (head == NULL)
    return;

    while (loop != NULL)
    {   
        if (godMode == true)
        {
            if (R == 255 && G < 255 && B == 0){
                G+=3;
            }
            else if (R > 0 && G == 255){
                R-=3;
            }
            else if (G == 255 && B < 255){
                B+=3;
            }
            //RGB Mode
            else if (G > 0 && B == 255){
                G-=3;
            }
            else if (B == 255 && R < 255){
                R+=3;
            }
            else if (B > 0 && R == 255){
                B-=3;
            }
        }
        else
        {
            R = 255;
            G = 0;
            B = 0;
        }

        SDL_SetRenderDrawColor(renderer,R,G,B,SDL_ALPHA_OPAQUE);
        SDL_Rect rectangle;
        rectangle = {loop->getX()*PAS,loop->getY()*PAS,PAS,PAS};
        SDL_RenderFillRect(renderer, &rectangle);
        SDL_RenderDrawRect(renderer, &rectangle);
        loop = loop->next;  
        
    }  
}

void Snake::setGamemode(bool gamemode)
{
    this->godMode = gamemode;
}
bool Snake::getGamemode()
{
    return godMode;
}
bool Snake::collisionMur()
{
    if (head->getX() > (SIZE-1) || head->getX() < 0 || head->getY() > (SIZE-1) || head->getY() < 0)
    {
        if(godMode == true)
        {
            if(head->getX() > (SIZE-1))
            {
                head->setX(0);
                return false;
            }
            if(head->getX() < 0)
            {
                head->setX((SIZE-1));
                return false;
            }
            if(head->getY() > (SIZE-1))
            {
                head->setY(0);
                return false;
            }
            if(head->getY() < 0)
            {
                head->setY((SIZE-1));
                return false;
            }
            else
            {
                return true;
            }
        }
        else
        {
            return true;
        }
   
    }
    else
    {
        return false;
    }

}

bool Snake::collisionSnake()
{
    bool hit = false;
    Segment* loop = head->next;

    while (loop != NULL)
    {

        if (head->getX() == loop->getX() && head->getY() == loop->getY())
        {
            hit = true;
            break;

        }
        loop = loop->next;
    }
    return hit;
}

int Snake::getLen()
{
    int counter = 0;
    Segment* loop = head->next;

    while (loop != NULL)
    {
        loop = loop->next;
        counter++;
    }
    return counter;
}