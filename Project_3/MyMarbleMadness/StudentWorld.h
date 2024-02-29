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
  bool addPea(int x, int y, int direction, int source);
  bool damageAll(int x, int y, Actor* acting);
  Actor* findActor(int x, int y);
  Actor* findActor(int x, int y, Actor* caller);
  bool canSwallowAt(int x , int y);
  void pickUp();
  bool isPlayerHere(int x , int y);
  void addPeas(int amount){m_player->addPeas(amount);}
  int getScore(){return score;}
  int getLevel(){return level;}
  int getLives(){return lives;}
  int getBonus(){return bonus;}
  bool findSight(int x, int y, int dx,int dy);

private:
  Player *m_player;
  std::vector<Actor*> actors; // for all the things
  int m_nCrystals;
  int score;
  int level;
  int lives;
  int bonus;
};

#endif // STUDENTWORLD_H_
