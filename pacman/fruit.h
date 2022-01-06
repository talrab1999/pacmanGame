#pragma once
#include "ghost.h"

class fruit :public ghost{
public:
	fruit(char c='c');
	void setRandomSymbol();
	void sleepFruit(map&);
	void setSleep(bool);
	bool getSleep();
	void wakeUpFruit(map&);
	void resetLocation(map&);

	//-------------------SET----------------//

	//-------------------GET----------------//
	
	//-------------------METHODS------------//


private:
	bool sleep;

};

