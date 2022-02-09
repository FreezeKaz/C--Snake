#include "fruit.hpp"
#include "snake.hpp"
#include "segment.hpp"


Fruit::Fruit(int fruitX,int fruitY,int formNb, Snake* snake)
{
    srand(time(NULL));
    Segment loop = snake->getHead();
    this->fruitX = (rand() % SIZE);
    this->fruitY = (rand() % SIZE);
    this->formNb = 0;

    while (loop.next == NULL)
    {
        if (loop.getX() == fruitX && loop.getY() == fruitY)
        {
            this->fruitX = (rand() % SIZE);
            this->fruitY = (rand() % SIZE);
        }
    }
    

}

Fruit::~Fruit(){}

int Fruit::getX()
{return fruitX;}

int Fruit::getY()
{return fruitY;}

int Fruit::getForm()
{return formNb;}


void Fruit::eaten(Snake * snake)
{  
    int i = 0;
    int dropRate[10] = {0,0,0,0,0,2,2,2,2,1};
    
    Segment loop = snake->getHead();
    
    this->fruitX = (rand() % SIZE);
    this->fruitY = (rand() % SIZE);
    this->formNb = dropRate[(rand()% 10)];

    while (loop.next == NULL)
    {
        if (loop.getX() == fruitX && loop.getY() == fruitY)
        {
            this->fruitX = (rand() % SIZE);
            this->fruitY = (rand() % SIZE);
        }
    }
}
