#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

int StudentWorld::init()
{
    string curLevel = "level0" + to_string(getLevel()) + ".txt";
    Level lev(assetPath());
    Level::LoadResult result = lev.loadLevel(curLevel);
    if (result == Level::load_fail_file_not_found ||result == Level:: load_fail_bad_format)
        return -1; 
        cerr << "Successfully loaded level" << endl;
		for (int x = 0; x < 16; x++) {
			for (int y = 0; y < 16; y++) {
				Level::MazeEntry ge = lev.getContentsOf(x, y);
				switch (ge)
				{
                    case Level::player:
                        m_player = new Player(this, x,y);
                        break;
                    case Level::wall:
                        actors.push_back(new Wall(this, x, y));
                        break;
                    default:
                        break;
				}
			}
		}
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you type q

    //setGameStatText("Game will end when you type q");
    m_player->doSomething();
    for(int actorI=0;actorI<actors.size();actorI++){
        actors[actorI]->doSomething();
    }
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    for(int actorI=0;actorI<actors.size();actorI++){
        delete actors[actorI];
    }
    actors.clear();
    delete m_player;
    m_player=nullptr;
}

StudentWorld::~StudentWorld(){
    // according to Spec destructor can just call clean up
    cleanUp();
}
bool StudentWorld::isSpaceAvailable(int x,int y){
    for(int i=0;i<actors.size();i++){
        if(actors[i]->getX()==x && actors[i]->getY()==y){
            return false;
        }
    }
    return true;
}