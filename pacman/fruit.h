#pragma once
#include "ghost.h"

class fruit :public ghost{
public:
	fruit(char c='c');

	//---------------SET----------------//
	void setRandomSymbol();
	void setSleep(bool);

	//---------------GET----------------//
	bool getSleep();

	//-------------Methods------------//
	void sleepFruit(map&);
	void wakeUpFruit(map&);
	void resetLocation(map&);

private:
	bool sleep;
};

