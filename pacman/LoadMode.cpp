#include "LoadMode.h"


void LoadMode::gameLoop() {
	bool running1 = true;
	bool testFail = false;
	char key1, key2;
	char res;
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

	//Read init fruit location from file.

	while (running1 && !testFail)
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
		//FruitMetEntity(Tinky_Winky, Po, Dipsy, player1, h);
		if (didGhostEatPacman(h, player1, Tinky_Winky, Po, key1, key2, running1)) {
			res = 'D';
			readAndCheckResult(myResult, readResult, frame, testFail, res);
			if (checkIfGameLost(player1, running1) == true) {
				if (!(getline(myResult, readResult).eof())) {
					testFail = true;
				}
				else if(testFail == false) {
					printRes(true, mySteps, myResult);
					continue;
				}
			}

			if (testFail == true) {
				printRes(false,mySteps, myResult);
				continue;
			}
		}


		if (player1.getDotsate() == h.getDots()-350) { //Check if game won     
			clearScreen();
			res = 'W';
			readAndCheckResult(myResult, readResult, frame, testFail, res);
			if (!(getline(myResult, readResult).eof())) {
				testFail = true;
			}
			if (testFail == true) {
				printRes(false,mySteps, myResult);
				continue;
			}
			screenFiles.pop();
			myResult.close();
			mySteps.close();
			if (screenFiles.empty()) {
				printRes(true, mySteps, myResult);
				running1 = false;
				continue;
			}
			h.setFilename(screenFiles.front());    //Loades next map
			prepareForNewGame(h, player1, Dipsy, Tinky_Winky, Po, key1, key2, frame);
			prepareFilesForLoadGame(screenFiles.front(), mySteps, myResult);
			continue;
		}

		moveGhostWithDir(Tinky_Winky, h);
		moveGhostWithDir(Po, h);
		//
	
		//
		if (didGhostEatPacman(h, player1, Tinky_Winky, Po, key1, key2, running1)) {
			res = 'D';
			readAndCheckResult(myResult, readResult, frame, testFail, res);
			if (checkIfGameLost(player1, running1) == true) {
				if (!(getline(myResult,readResult).eof())) {
					testFail = true;
				}
				else if (testFail == false) {
					printRes(true, mySteps, myResult);
					continue;
				}
			}

			if (testFail == true) {
				printRes(false, mySteps, myResult);
				continue;
			}
		}

		if (Dipsy.getLastMove() != (int)e_EntityAction::SLEEP) {
			if (Dipsy.getLastMove() == (int)e_EntityAction::WAKE_UP) {
				Dipsy.setRandomSymbol();
				getline(mySteps, readSteps, ' ');
				Dipsy.setY(stoi(readSteps));
				getline(mySteps, readSteps, ' ');
				Dipsy.setX(stoi(readSteps));
			}
			else {
				FruitMetEntity(Tinky_Winky, Po, Dipsy, player1, h);
				moveGhostWithDir(Dipsy, h);
				FruitMetEntity(Tinky_Winky, Po, Dipsy, player1, h);
			}
			Dipsy.display();
		}
		frame++;
		if (!getSilent()) {
			player1.displayPoints(h, getLegend().first, getLegend().second);
			player1.display();
			//Dipslays Ghosts 
			Tinky_Winky.display();
			Po.display();
			Sleep(speed/2);
		}

		if (frame == 141) {
			continue;
		}
		
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
	default:
		nextX = curr.getX();
		nextY = curr.getY();
	}
	curr.setX(nextX);
	curr.setY(nextY);
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

void LoadMode::readAndCheckResult(ifstream& myResult, string& readResult, unsigned long long int& frame, bool& testFail, char& res) {
	getline(myResult, readResult, ' ');
	//The char D indicates Pacman death and W for win
	if (readResult[0] != res) {
		testFail = true;
	}
	else {
		getline(myResult, readResult);
		if (frame != stoi(readResult)) {
			testFail = true;
		}
	}
}

void LoadMode::printRes(bool didPass,ifstream& mySteps, ifstream& myResult) {
	clearScreen();
	if(!didPass)
		cout << "Test Failed ";
	else
		cout << "Test Passed ";
	mySteps.close();
	myResult.close();
}

void LoadMode::readMoveFromSteps(string& readSteps, pacman& player1, ghost& Tinky_Winky, ghost& Po, fruit& Dipsy){

	player1.setLastMove(readSteps[0] - '0');
	Tinky_Winky.setLastMove(readSteps[1] - '0');
	Po.setLastMove(readSteps[2] - '0');
	Dipsy.setLastMove(readSteps[3] - '0');
}

