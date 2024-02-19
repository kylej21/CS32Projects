#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

// Actor stuff
Actor::Actor(StudentWorld *world, int imageId, double startX, double startY, int startDirection, double size)
:
GraphObject(imageId, startX, startY, startDirection, size),
m_world(world)
{setVisible(true);};
StudentWorld* Actor::getWorld(){return m_world;};

// Wall stuff
Wall::Wall(StudentWorld *world,double x,double y):
    Actor(world, IID_WALL, x, y, right, 1)
    {
    };

// Avatar stuff
Player::Player(StudentWorld *world, double x, double y):
    Actor(world, IID_PLAYER, x,y,right,1)  
{}
void Player::doSomething(){
    int character;
    // if the user clicked an arrow in this frame this if statement returns true
    // effective since we dont want to do anything if the player does not click a key
    // stores it in character
    if(getWorld()->getKey(character)){
        if(character==KEY_PRESS_LEFT){
                moveTo(getX()-1,getY());
                setDirection(left);
        }
        else if(character==KEY_PRESS_RIGHT){

                moveTo(getX()+1,getY());
                setDirection(right);

        }
        else if(character==KEY_PRESS_DOWN){
            
                moveTo(getX(),getY()-1);
                setDirection(down);

        }
        else if(character==KEY_PRESS_UP){
            
                moveTo(getX(),getY()+1);
                setDirection(up);
        }
    } 
}