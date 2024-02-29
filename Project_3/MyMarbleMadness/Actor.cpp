#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

// Actor stuff
Actor::Actor(StudentWorld *world, int imageId, double startX, double startY, int startDirection, double size)
:
GraphObject(imageId, startX, startY, startDirection, size),
m_world(world)
{setVisible(true);
    alive=true;
};
StudentWorld* Actor::getWorld(){return m_world;};

// Wall stuff
Wall::Wall(StudentWorld *world,double x,double y):
    Actor(world, IID_WALL, x, y, right, 1)
    {
    };
// living actor stuff
livingActor::livingActor(StudentWorld *world, int imageId, double x, double y, int direction, double size, int health):
    Actor(world,imageId,x,y,direction,size)
{m_health=health;}
void livingActor::damage(int amount){
    m_health-=amount;
    if(m_health<=0){
        setAlive(false);
    }
}
Consumable::Consumable(StudentWorld * world, int imageId, double x, double y)
:   Actor(world, imageId, x , y, right, 1) 
{}
Crystal::Crystal(StudentWorld * world, double x, double y)
:   Consumable(world, IID_CRYSTAL, x , y)
{}
void Crystal::doSomething(){
    if(getWorld()->isPlayerHere(getX(), getY())){
        getWorld()->pickUp();
        setAlive(false);
    }
}
Pit::Pit(StudentWorld * world, double x, double y):
    Actor(world, IID_PIT, x, y, right, 1)    
{}
void Pit::doSomething(){
    Actor * a = getWorld()->findActor(getX(), getY(),this);
    if(a!=nullptr && a->isPushable()){
        a->setAlive(false);
        setAlive(false);
        return;
    }
}
Marble::Marble(StudentWorld *world,double x,double y):
    livingActor(world, IID_MARBLE, x, y, right, 1,10)
    {
    };
bool Marble::push(int x, int y, int dir){
    switch(dir){
        case right:
            if(getWorld()->isSpaceAvailable(x+1,y)||getWorld()->canSwallowAt(x+1,y)){
                return true;
            }
            break;
        case up:
            if(getWorld()->isSpaceAvailable(x,y+1)||getWorld()->canSwallowAt(x,y+1)){
                return true;
            }
            break;
        case down:
            if(getWorld()->isSpaceAvailable(x,y-1)||getWorld()->canSwallowAt(x,y-1)){
                return true;
            }
            break;
        case left:
            if(getWorld()->isSpaceAvailable(x-1,y)||getWorld()->canSwallowAt(x-1,y)){
                return true;
            }
            break;
        default:
            return false;
            break;
    }
    return false;
}
// Avatar stuff
Player::Player(StudentWorld *world, double x, double y):
    livingActor(world, IID_PLAYER, x,y,right,1,20)  
{m_peas=20;}
void Player::doSomething(){
    if(getHealth()<=0){
        return;
    }
    
    int character;
    // if the user clicked an arrow in this frame this if statement returns true
    // effective since we dont want to do anything if the player does not click a key
    // stores it in character
    if(getWorld()->getKey(character)){
        if(character==KEY_PRESS_ESCAPE){
            damage(100); // 100 ensures the player has a negative health
        }
        else if(character==KEY_PRESS_SPACE){
            if(getPeas()>0){
                switch(getDirection()){
                    case up:
                        getWorld()->addPea(getX(),getY()+1,up,0);
                        break;
                    case down:
                        getWorld()->addPea(getX(),getY()-1,down,0);
                        break;
                    case left:
                        getWorld()->addPea(getX()-1,getY(),left,0);
                        break;
                    case right:
                        getWorld()->addPea(getX()+1,getY(),right,0);
                        break;
                }
            }
        }
        else if(character==KEY_PRESS_LEFT){
            if(getWorld()->isSpaceAvailable(getX()-1,getY())){
                moveTo(getX()-1,getY());
            }
            else{
                Actor * a = getWorld()->findActor(getX()-1,getY());
                if(a!=nullptr){   
                    if(a->isPushable()){
                        if(a->push(getX()-1,getY(),left)){
                            moveTo(getX()-1,getY());
                            a->moveTo(getX()-1,getY());
                        }
                    }
                    else if(a->canBeStepped()){
                        moveTo(getX()-1,getY());
                        a->consume();
                    }
                } 
            }    
            setDirection(left);    
        }
        else if(character==KEY_PRESS_RIGHT){
            if(getWorld()->isSpaceAvailable(getX()+1,getY())){
                moveTo(getX()+1,getY());
            }
            else{
                Actor * a = getWorld()->findActor(getX()+1,getY());
                if(a!=nullptr){   
                    if(a->isPushable()){
                        if(a->push(getX()+1,getY(),right)){
                            moveTo(getX()+1,getY());
                            a->moveTo(getX()+1,getY());
                        }
                    }
                    else if(a->canBeStepped()){
                        moveTo(getX()+1,getY());
                        a->consume();
                    }
                } 
            }    
            setDirection(right);
        }
        else if(character==KEY_PRESS_DOWN){
            if(getWorld()->isSpaceAvailable(getX(),getY()-1)){
                moveTo(getX(),getY()-1);
            }
            else{
                Actor * a = getWorld()->findActor(getX(),getY()-1);
                if(a!=nullptr){   
                    if(a->isPushable()){
                        if(a->push(getX(),getY()-1,down)){
                            moveTo(getX(),getY()-1);
                            a->moveTo(getX(),getY()-1);
                        }
                    }
                    else if(a->canBeStepped()){
                        moveTo(getX(),getY()-1);
                        a->consume();
                    }
                } 
            }    
            setDirection(down);
        }
        else if(character==KEY_PRESS_UP){
            if(getWorld()->isSpaceAvailable(getX(),getY()+1)){
                moveTo(getX(),getY()+1);
            }
            else{
                Actor * a = getWorld()->findActor(getX(),getY()+1);
                if(a!=nullptr){   
                    if(a->isPushable()){
                        if(a->push(getX(),getY()+1,up)){
                            moveTo(getX(),getY()+1);
                            a->moveTo(getX(),getY()+1);
                        }
                    }
                    else if(a->canBeStepped()){
                        moveTo(getX(),getY()+1);
                        a->consume();
                    }
                } 
            }    
            setDirection(up);
        }
    } 
}

//pea stuff
Pea::Pea(StudentWorld *world, double x, double y, int direction):
    Actor(world,IID_PEA,x,y,direction,1)
{
}
void Pea::doSomething(){
    if(isAlive()){
        if(getWorld()->damageAll(getX(),getY(),this)){
            setVisible(false);
            setAlive(false);
        }
    }
    switch(getDirection()){
        case up:         
            moveTo(getX(),getY()+1);
        break;
        case down:    
            moveTo(getX(),getY()-1);  
        break;
        case left:
            moveTo(getX()-1,getY());
        break;
        case right:
            moveTo(getX()+1,getY());
        break;
    }
    if(isAlive()){
        if(getWorld()->damageAll(getX(),getY(),this)){
            setVisible(false);
            setAlive(false);
        }
    }
}

// rage bot stuff
Robot::Robot(StudentWorld* world,int imageId, double x, double y, int direction):
    livingActor(world,imageId, x,y,direction,1,10)
{
    
    currentTick=1;
    m_ticks = (28-getWorld()->getLevel())/4;
    if(m_ticks<3){
        m_ticks =3;
    }
};
void Robot::doSomething(){
    if(currentTick==m_ticks){
        doRobotActivity();
        currentTick=1;
    }
    else{
        currentTick+=1;
    }
};
RageBot::RageBot(StudentWorld * world, double x, double y, int direction):
    Robot(world, IID_RAGEBOT, x, y, direction)
{
    if(direction==right){
        deltaX=1;
        deltaY=0;
    }
    else{
        deltaY=1;
        deltaX=0;
    }
};
void RageBot::doRobotActivity(){
    bool lineOfSight = getWorld()->findSight(getX()+deltaX,getY()+deltaY,deltaX,deltaY); //later set lineOfSight = findSight();
    if(lineOfSight){
        getWorld()->addPea(getX()+deltaX,getY()+deltaY,getDirection(),1);
    }
    else{
        if(getWorld()->isSpaceAvailable(getX()+deltaX,getY()+deltaY) || (getWorld()->findActor(getX()+deltaX,getY()+deltaY)->canBeStepped())){
            moveTo(getX()+deltaX,getY()+deltaY);
        }
        else{
            switch(getDirection()){
                case up:
                    deltaY=-1;
                    setDirection(down);
                break;
                case down:
                    deltaY=1;
                    setDirection(up);
                break;
                case left:
                    deltaX=1;
                    setDirection(right);
                break;
                case right:
                    deltaX=-1;
                    setDirection(left);
                break;
            }
        }
    }
}
Exit::Exit(StudentWorld* world, double x, double y):
    Actor(world, IID_EXIT, x, y, right, 1)
{
    setVisible(false);
};
void Exit::doSomething(){
    return;
}
Goodie::Goodie(StudentWorld* world, int imageId, double x, double y):
    Consumable(world,imageId, x, y)
{}
void Goodie::doSomething(){
    if(getWorld()->isPlayerHere(getX(), getY())){
        //play sound
        setAlive(false);
        doActivity();
    }
}
Ammo::Ammo(StudentWorld * world, double x, double y):
    Goodie(world, IID_AMMO, x, y)
{}
void Ammo::doActivity(){
    getWorld()->addPeas(20);
}