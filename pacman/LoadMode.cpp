#include "LoadMode.h"

void LoadMode::gameLoop1() {

	bool running1 = true;
	char key1, key2;
	unsigned long long int frame;   //can get realy high numbers...

	pacman player1;
	ghost Tinky_Winky;
	ghost Po;
	fruit Dipsy;
	map h;

	string readSteps = "";
	string readResult = "";
	ifstream mySteps, myResult;

	
	setSilent(getMode() == char(e_GameMode::LOAD_SILENT));
	
	resetScreens();		//Resets Queue of Screens
	getFiles();			//Fill Queue with screen files

	h.setFilename(screenFiles.front()); //Choose first map in alphabetical queue to play 

	prepareForNewGame(h, player1, Dipsy, Tinky_Winky, Po, key1, key2, frame);
	prepareFilesForLoadGame(screenFiles.front(), mySteps, myResult);


	while (running1)
	{
		getline(mySteps, readSteps, ' ');
		h.setmapat(player1.getY(), player1.getX(), ' ');

		if (!getSilent()) {
			player1.display(' ');
			switch (numGhosts) {
			case 3: Dipsy.display(h.getmapat(Dipsy.getY(), Dipsy.getX()));
			case 2: Tinky_Winky.display(h.getmapat(Tinky_Winky.getY(), Tinky_Winky.getX()));
			case 1: Po.display(h.getmapat(Po.getY(), Po.getX()));
			}
		}

		movePacmanWithDir(key1, player1, h, readSteps);  //moves the pacman with the direction from the file

		if (didGhostEatPacman(h, player1, Tinky_Winky, Po, key1, key2, running1) == true)
		{
			readAndCheckResult(myResult, readResult, frame, running1);
			if (checkIfGameLost(player1, running1) == true) {
				if (!myResult.eof()) {
					running1 = false;
				}
			}

			if (running1 == false) {
				exitLoop(running1, mySteps, myResult);
				continue;
			}
		}

		if ((FruitMetEntity(Tinky_Winky, Po, Dipsy, player1, h) == true)) 
			/* {
			Dipsy.sleepFruit(h);
			Dipsy.setLastMove(int(e_EntityAction::SLEEP));
			Dipsy.resetCounter();
		}*/

		if (player1.getDotsate() == h.getDots()) { //Check if game won     

			clearScreen();
			screenFiles.pop();
			//myResult << "W " << frame << "\n";
			myResult.close();
			mySteps.close();
			if (screenFiles.empty()) {
				displaywin();
				running1 = false;
				continue;
			}
			cout << "Good luck in the next map" << endl;
			system("pause");
			clearScreen();
			h.setFilename(screenFiles.front());    //Loades next map
			prepareForNewGame(h, player1, Dipsy, Tinky_Winky, Po, key1, key2, frame);
			prepareFilesForLoadGame(screenFiles.front(), mySteps, myResult);
			continue;
		}

		if (frame % ghostspeed == 0) { //Every Second frame ghosts move
			ghostMove(Tinky_Winky, h, player1);
			ghostMove(Po, h, player1);
			//writeFile += to_string(Tinky_Winky.getLastMove());
			//writeFile += to_string(Po.getLastMove());

			if ((FruitMetEntity(Tinky_Winky, Po, Dipsy, player1, h) == true)) {
				Dipsy.sleepFruit(h);
				Dipsy.setLastMove(int(e_EntityAction::SLEEP));
				Dipsy.resetCounter();
			}
			if (Dipsy.getSleep() == false) { //Fruit not asleep
				ghostMove(Dipsy, h, player1);
				//writeFile += to_string(Dipsy.getLastMove());

				if ((FruitMetEntity(Tinky_Winky, Po, Dipsy, player1, h) == true)) {
					Dipsy.sleepFruit(h);
					Dipsy.setLastMove(int(e_EntityAction::SLEEP));
					Dipsy.resetCounter();
				}
			}
			else {	// Fruit asleep
				if (Dipsy.getTurnCounter() == 50) {
					Dipsy.wakeUpFruit(h);
					Dipsy.setLastMove(int(e_EntityAction::WAKE_UP));
					//writeFile += to_string(Dipsy.getLastMove());
					//writeFile += " " + to_string(Dipsy.getY()) + " " + to_string(Dipsy.getX());
					Dipsy.setLastMove();
				}
				else
					//writeFile += to_string(Dipsy.getLastMove());

					Dipsy.setTurnCounter(Dipsy.getTurnCounter() + 1);
			}
		}
		//else { //Not ghosts turn
		//	writeFile += to_string(int(e_EntityAction::STAY));	//Ghost1 
		//	writeFile += to_string(int(e_EntityAction::STAY));	//Ghost2 

		//	if (Dipsy.getLastMove() == int(e_EntityAction::SLEEP))	//Fruit 
		//		writeFile += to_string(Dipsy.getLastMove());
		//	else
		//		writeFile += to_string(int(e_EntityAction::STAY));
		//}

		//mySteps << writeFile << " ";
		frame++;

		if (didGhostEatPacman(h, player1, Tinky_Winky, Po, key1, key2, running1) == true)
		{
			//myResult << "D " << frame << "\n";
			if (checkIfGameLost(player1, running1) == true) {
				mySteps.close();
				myResult.close();
			}
			continue;
		}
		if (!getSilent()) {

			player1.displayPoints(h, getLegend().first, getLegend().second);
			player1.display();

			switch (numGhosts) {  //Dipslays Ghosts and fruit
			case 3: Dipsy.display();
			case 2: Tinky_Winky.display();
			case 1: Po.display();
			}

			Sleep(speed);
		}
	}
	myResult.close();
	mySteps.close();
}

void LoadMode::gameLoop() {

	bool running1 = true;
	char key1, key2;
	unsigned long long int frame;   //can get realy high numbers...

	pacman player1;
	ghost Tinky_Winky;
	ghost Po;
	fruit Dipsy;
	map h;

	string readSteps = "";
	string readResult = "";
	ifstream mySteps, myResult;


	setSilent(getMode() == char(e_GameMode::LOAD_SILENT));

	resetScreens();		//Resets Queue of Screens
	getFiles();			//Fill Queue with screen files

	h.setFilename(screenFiles.front()); //Choose first map in alphabetical queue to play 

	prepareForNewGame(h, player1, Dipsy, Tinky_Winky, Po, key1, key2, frame);
	prepareFilesForLoadGame(screenFiles.front(), mySteps, myResult);

	while (running1)
	{
		getline(mySteps, readSteps, ' ');
		readMoveFromSteps(readSteps, player1, Tinky_Winky, Po, Dipsy);

		h.setmapat(player1.getY(), player1.getX(), ' ');

		if (!getSilent()) {
			player1.display(' ');
			switch (numGhosts) {
			case 3: Dipsy.display(h.getmapat(Dipsy.getY(), Dipsy.getX()));
			case 2: Tinky_Winky.display(h.getmapat(Tinky_Winky.getY(), Tinky_Winky.getX()));
			case 1: Po.display(h.getmapat(Po.getY(), Po.getX()));
			}
		}

		movePacmanWithDir(key1, player1, h, readSteps);  //moves the pacman with the direction from the file
		FruitMetEntity(Tinky_Winky, Po, Dipsy, player1, h);
		if (didGhostEatPacman(h, player1, Tinky_Winky, Po, key1, key2, running1))
			checkIfGameLost(player1, running1);
		moveGhostWithDir(Tinky_Winky, h);
		moveGhostWithDir(Po, h);
		FruitMetEntity(Tinky_Winky, Po, Dipsy, player1, h);
		if (didGhostEatPacman(h, player1, Tinky_Winky, Po, key1, key2, running1))
			checkIfGameLost(player1, running1);
		moveGhostWithDir(Dipsy, h);

	}
}
void LoadMode::prepareFilesForLoadGame(string fileName, ifstream& mySteps, ifstream& myResult)
{

	string fixName = fileName;
	int i = 2;

	while (fixName[i] != '.') {
		i++;
	}
	fixName = fixName.substr(0, i);

	mySteps.open(fixName + ".steps", ios::in);
	myResult.open(fixName + ".result", ios::in);

}

void LoadMode::movePacmanWithDir(char& key1, pacman& player1, map& h, string& readFile) {

	key1 = readFile[0];

	switch (key1) {
	case '0':
		player1.move_up(h);
		break;

	case '1':
		player1.move_down(h);
		break;

	case '2':
		player1.move_left(h);
		break;

	case '3':
		player1.move_right(h);
		break;

	case '4':
		player1.stop(h);
		break;
	}
}
void LoadMode::moveGhostWithDir(ghost& curr, map& h) {

	int nextY, nextX;
	
	switch (curr.getLastMove()) {

	case 0: nextY = curr.getY() - 1; //UP
		nextX = curr.getX();
		break;
	case 1: nextY = curr.getY() + 1; //Down
		nextX = curr.getX();
		break;
	case 2: nextY = curr.getY();  //Left
		nextX = curr.getX() - 1;
		break;
	case 3: nextY = curr.getY(); //Right
		nextX = curr.getX() + 1;
		break;
	}
}

bool LoadMode::didGhostEatPacman(map& h, pacman& player1, ghost& Tinky_Winky, ghost& Po, char& key1, char& key2, bool& running1) {
	if ((Tinky_Winky.getX() == player1.getX() && Tinky_Winky.getY() == player1.getY()) || (Po.getX() == player1.getX() && Po.getY() == player1.getY()))
	{	//If reached this point, one life is lost
		player1.setLives(player1.getLives() - 1);

		if (!getSilent()) {
			Sleep(4000);
			player1.displayLives(h, getLegend().first, getLegend().second);
			Tinky_Winky.display(h.getmapat(Tinky_Winky.getY(), Tinky_Winky.getX()));
			Po.display(h.getmapat(Po.getY(), Po.getX()));
		}
		//Resets Entities
		player1.resetEntity();
		Tinky_Winky.resetEntity();
		Po.resetEntity();

		return true;
	}
	return false;
}

void LoadMode::setSilent(bool silent) {
	silentMode = silent;
}

bool LoadMode::getSilent() {
	return silentMode;
}

void LoadMode::readAndCheckResult(ifstream& myResult, string& readResult, unsigned long long int& frame, bool& running1) {
	getline(myResult, readResult, ' ');
	//The char D indicates Pacman death
	if (readResult[0] != 'D') {
		running1 = false;
	}
	else {
		getline(myResult, readResult);
		if (frame != stoi(readResult)) {
			running1 = false;
		}
	}
}

void LoadMode::exitLoop(bool& running1, ifstream& mySteps, ifstream& myResult) {
	cout << "Test Failed ";
	mySteps.close();
	myResult.close();
}

void LoadMode::readMoveFromSteps(string& readSteps, pacman& player1, ghost& Tinky_Winky, ghost& Po, fruit& Dipsy){

	player1.setLastMove(readSteps[0]);
	Tinky_Winky.setLastMove(readSteps[1]);
	Po.setLastMove(readSteps[2]);
	Dipsy.setLastMove(readSteps[3]);
}

