#pragma once
#include "map.h"
#include "Entity.h"
#include <time.h>
#include <cstdlib>
class ghost :public Entity {
private:

	char difficulty;
	int goodGhostCounter;
	int turnCounter;
	
public:
	ghost(char diff='c');

	void move(short, short);
	void resetCounter();

	///////////SET//////////
	void setDifficulty(char);
	void setGoodCounter(int);
	void setTurnCounter(int);

	///////////GET//////////
	char getDifficulty();
	int getGoodCounter();
	int getTurnCounter();
};
