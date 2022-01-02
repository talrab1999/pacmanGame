#include <iostream>
#include "game.h"
#include "SaveMode.h"
#include "LoadMode.h"

using namespace std;

void main(int argc, char** argv)
{
	srand(time(0));
	game* Game = nullptr;
	
	if (argc == 1) {
		Game = new game();
		Game->setMode(char(e_GameMode::SIMPLE));
		Game->runMenu();
	}
	else if (strcmp(argv[1], "-save") == 0) {
		Game = new SaveMode();
		Game->setMode(char(e_GameMode::SAVE));
		Game->runMenu();
	}
	else if (strcmp(argv[1], "-load") == 0) {
		Game = new LoadMode();

		if (argc == 3) {
			if (strcmp(argv[2], "[-silent]") == 0) {
				Game->setMode(char(e_GameMode::LOAD_SILENT));
				Game->gameLoop(true);
			}
		}
		else {
			Game->setMode(char(e_GameMode::LOAD));
			Game->gameLoop();
		}
	}
	delete Game;
}

//
//	
//	if (strcmp(argv[1], "-load") == 0) {
//		Game = new LoadMode();
//		Game->setMode(char(e_GameMode::LOAD));
//
//		if (argc == 3)
//			if (strcmp(argv[2], "-silent") == 0) {
//				Game->setMode(char(e_GameMode::LOAD_SILENT));
//				Game->gameLoop(true);
//			}
//			else {
//				Game->gameLoop();
//			}
//	}
//
//	else {
//		if (strcmp(argv[1], "-save") == 0)
//			Game = new SaveMode();
//			Game->setMode(char(e_GameMode::SAVE));
//		else
//			Game->setMode(char(e_GameMode::SIMPLE));
//
//		while (input != '9') {
//			Game->goToOption(input);
//		}
//	}
//
//}
