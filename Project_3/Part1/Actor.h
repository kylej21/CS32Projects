#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;

class Actor : public GraphObject{
    public: 
        Actor(StudentWorld *world, int imageId, double startX, double startY, int startDirection, double size);
        virtual void doSomething() = 0;
        StudentWorld* getWorld();
    private:
        StudentWorld* m_world;
};
class Wall : public Actor{
    public:
        Wall(StudentWorld *world,double x,double y);
        virtual void doSomething(){return;};

    private:
    // nothing??
};

class Player : public Actor{
    public:
        Player(StudentWorld *world, double x, double y);
        virtual void doSomething();
    private:
};

#endif // ACTOR_H_
