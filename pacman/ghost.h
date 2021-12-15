#pragma once
#include "Entity.h"
#include "map.h"
#include <time.h>
#include <cstdlib>
class ghost :public Entity {
private:
	bool edible;
	short lastmove;
public:
	ghost();
	void move_rand(map&);
	//make new reset that gets x,y
	void reset1();
	void reset2();
};
