#pragma once
#include "ghost.h"

class fruit :public ghost{
public:
	fruit(char c='c');

	//Set Methods
	void setRandomSymbol();
	void setSleep(bool);

	//Get Methods
	bool getSleep();

	//Methods
	void sleepFruit(map&);
	void wakeUpFruit(map&);
	void resetLocation(map&);

private:
	bool sleep;
};

