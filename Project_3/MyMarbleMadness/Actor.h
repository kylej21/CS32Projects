#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;

class Actor : public GraphObject{
    public: 
        Actor(StudentWorld *world, int imageId, double startX, double startY, int startDirection, double size);
        virtual void doSomething() = 0;
        virtual void damage(int amount){return;};
        StudentWorld* getWorld();
        bool isAlive(){return alive;};
        void setAlive(bool newStatus){alive = newStatus;};
        virtual bool isPushable(){return false;};
        virtual bool push(int x, int y, int dir){return false;};
        virtual bool canSwallow(){return false;};
        virtual bool isPassable(){return false;};
        virtual bool canBeStepped(){return false;};
        virtual void consume(){return;};

    private:
        StudentWorld* m_world;
        bool alive;

};
class Consumable : public Actor{
    public:
        Consumable(StudentWorld * world,int imageId, double x, double y);
        virtual void doSomething() = 0;
        virtual bool canBeStepped(){return true;};
        virtual bool isPassable(){return true;};
        virtual void consume(){ setAlive(false);};

};
class Crystal : public Consumable{
    public:    
        Crystal(StudentWorld * world, double x, double y);
        virtual void doSomething();

};
class Goodie : public Consumable{
    public:
        Goodie(StudentWorld * world,int imageId, double x, double y);
        virtual void doSomething();
        virtual void doActivity()=0;
};
class Ammo : public Goodie{
    public:
        Ammo(StudentWorld * world, double x, double y);
        virtual void doActivity();
};
class Pit : public Actor{
    public:
        Pit(StudentWorld * world, double x, double y);
        virtual void doSomething();
        virtual bool canSwallow(){return true;};
        virtual bool isPassable(){return true;};
};
class livingActor : public Actor{
    public:
        livingActor(StudentWorld *world, int imageId, double x, double y, int direction, double size, int health);
        virtual void doSomething() = 0;
        int getHealth(){return m_health;};
        virtual void damage(int amount);
        virtual bool push(int x, int y, int dir){return false;};

    private:
        int m_health;
};
class Wall : public Actor{
    public:
        Wall(StudentWorld *world,double x,double y);
        virtual void doSomething(){return;};
    private:
    // nothing??
};
class Marble : public livingActor{
    public:
        Marble(StudentWorld *world, double x, double y);
        virtual void doSomething(){return;};
        virtual bool isPushable(){return true;};
        virtual bool push(int x, int y, int dir);
    private:
};
class Pea : public Actor{
    public:
        Pea(StudentWorld *world, double x, double y, int direction);
        virtual void doSomething();
    private:
};
class Player : public livingActor{
    public:
        Player(StudentWorld *world, double x, double y);
        virtual void doSomething();
        int getPeas(){return m_peas;};
        void usePea(){m_peas-=1;};
        void addPeas(int amount){m_peas+=amount;}
    private:
        int m_peas;
};
class Robot : public livingActor{
    public:
        Robot(StudentWorld *world, int imageId, double x, double y, int direction);
        virtual void doSomething();
        virtual void doRobotActivity()=0;
    private:  
        int m_ticks;
        int currentTick;
};
class RageBot : public Robot{
    public:
        RageBot(StudentWorld * world, double x, double y, int direction);
        virtual void doRobotActivity();
    private:
        int deltaX;
        int deltaY;
};
class Exit : public Actor{
    public:
        Exit(StudentWorld *world, double x, double y);
        virtual void doSomething();
        virtual bool canBeStepped(){return true;};
        virtual bool isPassable(){return true;};
};
#endif // ACTOR_H_
