#include <iostream>
#include "game.h"
using namespace std;

void main(int argc, char** argv)
{
	srand(time(0));
	game Game;
	char input = 0;

	if (strcmp(argv[1], "-save") == 0) {
		//play Save Mode
		Game.setMode(char(e_GameMode::SAVE));
		cout <<"argv1 is "<< argv[1] << endl;
//	}
//	else if (strcmp(argv[1], "-load") == 0) {
//		Game.setMode(char(e_GameMode::LOAD));
//		if (argc == 3)
//			if (strcmp(argv[2], "-silent") == 0) {
//				Game.gameLoop(true);
//			}
//			else {
//				Game.gameLoop(false);
//			}
//	}
//	//No main parameters
//	else {
//		while (input != '9') {
//			Game.goToOption(input);
//		}
//	}
}
