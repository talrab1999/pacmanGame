#pragma once
#include "ghost.h"

class fruit :public ghost{
public:
	fruit(char c='c');
	//-------------------SET----------------//
	//void setRandSymbol() { setSymbol(fruitRandSymbol()); }		 //Sets Rand value between 5-9

	//-------------------GET----------------//


	//-------------------METHODS----------------//
	//char fruitRandSymbol() { return rand() % 5 + 5 + '0'; }		 //Calculates a rand number between 5 to 9 and sends the char's ASCII value
	//void fruitDissapear() { setSymbol('%'); }					//OPTION 1: method that changes the fruit symbol to space.

private:
	bool m_metEntity;
};

