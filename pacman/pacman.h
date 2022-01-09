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
	void setPoints(short);
	short getPoints() const;
	void displayPoints(map&,int,int) const;
	void displayLives(map&,int,int);
	void move_up(map&);
	void move_down(map&);
	void move_left(map&);
	void move_right(map&);
	void stop(map&);

};
