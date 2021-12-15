#pragma once
#include "Entity.h"
#include "map.h"
using namespace std;

class pacman :public Entity {
private:
	short points, dotsate;
public:
	pacman();
	void setDotsate(short);
	short getDotsate() const;
	short getPoints() const;
	void displayPoints(map&) const;
	void displayLives(map&);
	void reset();
	void move_up(map&);
	void move_down(map&);
	void move_left(map&);
	void move_right(map&);
	void stop(map&);
};
