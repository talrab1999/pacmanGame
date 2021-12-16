#pragma once
#include "Entity.h"
#include "map.h"
#include <time.h>
#include <cstdlib>
class ghost :public Entity {
private:
	//bool edible;
	//short lastmove;
	short difficulty;
public:
	ghost();
	//void move_rand(map&);
	void move(short, short);
	//make new reset that gets x,y
	void reset(int, int);
	//void reset2();
};
