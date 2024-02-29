#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include <string>
#include "Actor.h"
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  ~StudentWorld();
  virtual int init();
  virtual int move();
  virtual void cleanUp();
  bool isSpaceAvailable(int x, int y);
private:
  Player *m_player;
  std::vector<Actor*> actors; // for all the things
};

#endif // STUDENTWORLD_H_
