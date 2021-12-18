#pragma once
#include "Entity.h"
#include "map.h"
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
	//make new reset that gets x,y
	void reset(int, int);
	//void reset2();

	void setDifficulty(char);
	void setGoodCounter(int);
	void setTurnCounter(int);


	char getDifficulty();
	int getGoodCounter();
	int getTurnCounter();
};
