#pragma once
#include "map.h"
#include "Entity.h"
#include <time.h>
#include <cstdlib>
class ghost :public Entity {
private:
	//bool edible;
	//short lastmove;
	char difficulty;
	int goodGhostCounter;
	int turnCounter;
	
public:
	ghost(char);
	//void move_rand(map&);
	void move(short, short);

	void setDifficulty(char);
	void setGoodCounter(int);
	void setTurnCounter(int);


	char getDifficulty();
	int getGoodCounter();
	int getTurnCounter();
	void resetCounter();
};
