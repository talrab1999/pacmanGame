#include "game.h"

bool game::isValid(int row, int col)
{
	return (row >= 0) && (row < ROWS) && (col >= 0) && (col < COLS);
}

bool game::isUnBlocked(char grid[][COLS], int row, int col)
{
	// Returns true if the cell is not blocked else false
	if (grid[row][col] == '#')
		return (false);
	else if (grid[row][col] == '!')
		return (false);
	else
		return (true);
}

bool game::isDestination(int row, int col, Pair dest)
{
	if (row == dest.first && col == dest.second)
		return (true);
	else
		return (false);
}

int game::calculateHValue(int row, int col, Pair dest)
{
	return abs(row - dest.first) + abs(col - dest.second);
}

Pair game::tracePath(cell cellDetails[][COLS], Pair dest)
{
	int row = dest.first;
	int col = dest.second;

	stack<Pair> Path;

	while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col)) {
		Path.push(make_pair(row, col));
		int temp_row = cellDetails[row][col].parent_i;
		int temp_col = cellDetails[row][col].parent_j;
		row = temp_row;
		col = temp_col;
	}
	int i = 0;
	Pair target;
	Path.push(make_pair(row, col));
	while (!Path.empty()) {
		Pair p = Path.top();
		if (i == 1) {
			target = p;
		}
		Path.pop();
		//printf("-> (%d,%d) ", p.first, p.second);
		//gotoxy(p.second, p.first+1);
		//cout << "*";
		i++;
	}

	return target;
}

Pair game::aStarSearch(char grid[][COLS], Pair src, Pair dest)
{
	// If the source is out of range
	/*if (isValid(src.first, src.second) == false) {
		printf("Source is invalid\n");
		return;
	}

	// If the destination is out of range
	if (isValid(dest.first, dest.second) == false) {
		printf("Destination is invalid\n");
		return;
	}

	// Either the source or the destination is blocked
	if (isUnBlocked(grid, src.first, src.second) == false || isUnBlocked(grid, dest.first, dest.second) == false) {
		printf("Source or the destination is blocked\n");
		return;
	}

	// If the destination cell is the same as source cell
	if (isDestination(src.first, src.second, dest) == true) {
		printf("We are already at the destination\n");
		return;
	}*/

	// Create a closed list and initialise it to false which
	// means that no cell has been included yet This closed
	// list is implemented as a boolean 2D array
	bool closedList[ROWS][COLS];
	memset(closedList, false, sizeof(closedList));

	// Declare a 2D array of structure to hold the details
	// of that cell
	cell cellDetails[ROWS][COLS];

	int i, j;

	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++) {
			cellDetails[i][j].f = 1000;
			cellDetails[i][j].g = 1000;
			cellDetails[i][j].h = 1000;
			cellDetails[i][j].parent_i = -1;
			cellDetails[i][j].parent_j = -1;
		}
	}

	// Initialising the parameters of the starting node
	i = src.first, j = src.second;
	cellDetails[i][j].f = 0;
	cellDetails[i][j].g = 0;
	cellDetails[i][j].h = 0;
	cellDetails[i][j].parent_i = i;
	cellDetails[i][j].parent_j = j;

	/*
	Create an open list having information as-
	<f, <i, j>>
	where f = g + h,
	and i, j are the row and column index of that cell
	Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
	This open list is implemented as a set of pair of
	pair.*/
	set<pPair> openList;

	// Put the starting cell on the open list and set its
	// 'f' as 0
	openList.insert(make_pair(0, make_pair(i, j)));

	// We set this boolean value as false as initially
	// the destination is not reached.
	bool foundDest = false;
	Pair target;
	while (!openList.empty()) {
		pPair p = *openList.begin();

		// Remove this vertex from the open list
		openList.erase(openList.begin());

		// Add this vertex to the closed list
		i = p.second.first;
		j = p.second.second;
		closedList[i][j] = true;

		// To store the 'g', 'h' and 'f' of the 8 successors
		int gNew, hNew, fNew;

		//----------- 1st Successor (up) ------------

		// Only process this cell if this is a valid one
		if (isValid(i - 1, j) == true) {
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i - 1, j, dest) == true) {
				// Set the Parent of the destination cell
				cellDetails[i - 1][j].parent_i = i;
				cellDetails[i - 1][j].parent_j = j;
				//printf("The destination cell is found\n");
				target = tracePath(cellDetails, dest);
				foundDest = true;
				//free(cellDetails);
				return target;
			}
			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i - 1][j] == false && isUnBlocked(grid, i - 1, j) == true) {
				gNew = cellDetails[i][j].g + 1;
				hNew = calculateHValue(i - 1, j, dest);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to
				// the open list. Make the current square
				// the parent of this square. Record the
				// f, g, and h costs of the square cell
				//			 OR
				// If it is on the open list already, check
				// to see if this path to that square is
				// better, using 'f' cost as the measure.
				if (cellDetails[i - 1][j].f == FLT_MAX || cellDetails[i - 1][j].f > fNew) {
					openList.insert(make_pair(fNew, make_pair(i - 1, j)));

					// Update the details of this cell
					cellDetails[i - 1][j].f = fNew;
					cellDetails[i - 1][j].g = gNew;
					cellDetails[i - 1][j].h = hNew;
					cellDetails[i - 1][j].parent_i = i;
					cellDetails[i - 1][j].parent_j = j;
				}
			}
		}

		//----------- 2nd Successor (down) ------------

		if (isValid(i + 1, j) == true) {

			if (isDestination(i + 1, j, dest) == true) {
				cellDetails[i + 1][j].parent_i = i;
				cellDetails[i + 1][j].parent_j = j;
				//printf("The destination cell is found\n");
				target = tracePath(cellDetails, dest);
				foundDest = true;
				//free(cellDetails);
				return target;
			}

			else if (closedList[i + 1][j] == false && isUnBlocked(grid, i + 1, j) == true) {
				gNew = cellDetails[i][j].g + 1;
				hNew = calculateHValue(i + 1, j, dest);
				fNew = gNew + hNew;

				if (cellDetails[i + 1][j].f == FLT_MAX || cellDetails[i + 1][j].f > fNew) {
					openList.insert(make_pair(fNew, make_pair(i + 1, j)));
					cellDetails[i + 1][j].f = fNew;
					cellDetails[i + 1][j].g = gNew;
					cellDetails[i + 1][j].h = hNew;
					cellDetails[i + 1][j].parent_i = i;
					cellDetails[i + 1][j].parent_j = j;
				}
			}
		}

		//----------- 3rd Successor (right) ------------

		if (isValid(i, j + 1) == true) {

			if (isDestination(i, j + 1, dest) == true) {
				cellDetails[i][j + 1].parent_i = i;
				cellDetails[i][j + 1].parent_j = j;
				//printf("The destination cell is found\n");
				target = tracePath(cellDetails, dest);
				foundDest = true;
				//free(cellDetails);
				return target;
			}

			else if (closedList[i][j + 1] == false && isUnBlocked(grid, i, j + 1) == true) {
				gNew = cellDetails[i][j].g + 1;
				hNew = calculateHValue(i, j + 1, dest);
				fNew = gNew + hNew;

				if (cellDetails[i][j + 1].f == FLT_MAX || cellDetails[i][j + 1].f > fNew) {
					openList.insert(make_pair(fNew, make_pair(i, j + 1)));
					cellDetails[i][j + 1].f = fNew;
					cellDetails[i][j + 1].g = gNew;
					cellDetails[i][j + 1].h = hNew;
					cellDetails[i][j + 1].parent_i = i;
					cellDetails[i][j + 1].parent_j = j;
				}
			}
		}

		//----------- 4th Successor (left) ------------

		if (isValid(i, j - 1) == true) {

			if (isDestination(i, j - 1, dest) == true) {
				cellDetails[i][j - 1].parent_i = i;
				cellDetails[i][j - 1].parent_j = j;
				//printf("The destination cell is found\n");
				target = tracePath(cellDetails, dest);
				foundDest = true;
				//free(cellDetails);
				return target;
			}

			else if (closedList[i][j - 1] == false && isUnBlocked(grid, i, j - 1) == true) {
				gNew = cellDetails[i][j].g + 1;
				hNew = calculateHValue(i, j - 1, dest);
				fNew = gNew + hNew;

				if (cellDetails[i][j - 1].f == FLT_MAX || cellDetails[i][j - 1].f > fNew) {
					openList.insert(make_pair(fNew, make_pair(i, j - 1)));
					cellDetails[i][j - 1].f = fNew;
					cellDetails[i][j - 1].g = gNew;
					cellDetails[i][j - 1].h = hNew;
					cellDetails[i][j - 1].parent_i = i;
					cellDetails[i][j - 1].parent_j = j;
				}
			}
		}
	}

	/*if (foundDest == false)
		printf("Failed to find the Destination Cell\n");*/
		//return;
}

char instructions[15][32] = {
	"+#############################+",
	"|  LEFT     |     a or A      |",
	"|#############################|",
	"|#############################|",
	"|  RIGHT    |     d or D      |",
	"|#############################|",
	"|#############################|",
	"|  UP       |     w or W      |",
	"|#############################|",
	"|#############################|",
	"|  DOWN     |     x or X      |",
	"|#############################|",
	"|#############################|",
	"|  STAY     |     s or S      |",
	"+#############################+"
};

char win[9][63] = {
	"##########################################################",
	"#                                                        #",
	"#  #   #  #####  #   #     #           #   #  #     #    #",
	"#   # #   #   #  #   #      #         #    #  # #   #    #",
	"#    #    #   #  #   #       #   #   #     #  #  #  #    #",
	"#    #    #   #  #   #        # # # #      #  #   # #    #",
	"#    #    #####  #####         #   #       #  #     #    #",
	"#                                                        #",
	"##########################################################",
};

char lose[9][63] = {
	"##########################################################",
	"#                                                        #",
	"#  #   #  #####  #   #     #      #####  #####  #####    #",
	"#   # #   #   #  #   #     #      #   #  #      #        #",
	"#    #    #   #  #   #     #      #   #  #####  #####    #",
	"#    #    #   #  #   #     #      #   #      #  #        #",
	"#    #    #####  #####     #####  #####  #####  #####    #",
	"#                                                        #",
	"##########################################################",
};

string game::choices[3] = {
	"1 - Start a new game",
	"8 - Instructions and keys",
	"9 - Quit" };

game::game()
{
	numGhosts = 2;
	speed = 100;
	ghostspeed = 2;      //means X2 slower than the pacman
	startLives = 3;
	goToOption(0);
}

void game::gotoxy(int x, int y)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y };

	SetConsoleCursorPosition(hStdout, position);
}

void game::displayChoices() const
{
	for (auto x : choices)
		cout << x << "\n";
}
void game::displayChoices(short curr) const {
	for (auto x : choices) {
		if (x != choices[curr])
			cout << x << "\n";
	}
}

void game::goToOption(short in)
{
	clearScreen();
	switch (in) {
	case 0:
		displayChoices();
		break;
	case 1:
		gameLoop();
		break;
	case 8: 
		displayInstructions();
		clearScreen();
		goToOption(0);
		break;
	case 9: 
		exit(0);
		break;
	}
}


void game::clearScreen() const
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { 0, 0 };
	SetConsoleCursorPosition(hStdout, position);
	/*for (short j = 0; j < 80; j++) {
		for (short i = 0; i < 40; i++) {
			position = { i, j };
			cout << " ";
		}
	}*/
	position = { 0,0 };
	SetConsoleCursorPosition(hStdout, position);
	system("CLS");
}


void game::displayInstructions() const
{
	for (int i = 0; i < 15; i++) {
		printf("%s\n", instructions[i]);
	}
	cout << "\nUse the controls above to move the pacman." << endl;
	cout << "Eat all the breadcrumbs to win the game." << endl;
	cout << "You lose 1 life each time the ghost hunts you." << endl;
	cout << "Once lost all 3 lifes, you lose and the game ends." << endl;
	cout << "Good luck!\n\n";
	cout << "Press any key to go back to the menu..." << endl;
	short flag;
	flag = _getch();
}

void game::displaywin() const
{
	for (int i = 0; i < 9; i++) {
		printf("%s\n", win[i]);
		Sleep(100);
	}
	Sleep(1000);
	cout << "\npress any key to go back to the menu..." << endl;
	short flag;
	flag = _getch();
}

void game::displaylose() const
{
	for (int i = 0; i < 9; i++) {
		printf("%s\n", lose[i]);
		Sleep(100);
	}
	Sleep(1000);
	cout << "\npress any key to go back to the menu..." << endl;
	short flag;
	flag = _getch();

}

string game::getFilename() const {
	return filename;
}

void game::setFilename(string f) {
	filename = f;
}

void game::gameLoop() {
	srand(time(0));
	bool running1 = true;
	bool running2 = true;
	bool checkInput;
	short nextX, nextY;
	unsigned long long int frame = 0;   //can get realy high numbers...

	pacman player1;
	ghost Tinky_Winky;
	ghost Po;
	map h;
	Pair move, src, dest;
	h.fillmap();
	h.fillboard();
	player1.setLives(startLives);
	/////////
	running1 = true;
	char key1 = 's', key2 = 's';
	h.ShowMap();
	player1.displayLives(h);

	player1.display();
	h.setmapat(player1.getY(), player1.getX(), player1.getSymbol());

	switch (numGhosts) {
	case 2:
		Tinky_Winky.reset(15,7);
		Tinky_Winky.display();
	case 1:
		Po.reset(30,7);
		Po.display();
	}

	/*while (running2) {
		/*running1 = true;
		char key1 = 's' , key2 = 's';
		h.ShowMap();
		player1.displayLives(h);

		player1.display();
		h.setmapat(player1.getY(), player1.getX(), player1.getSymbol());

		switch (numGhosts) {
		case 2:
			Tinky_Winky.reset2();
			Tinky_Winky.display();
		case 1:
			Po.reset1();
			Po.display();
		}*/

	while (running1)
	{

		player1.display(' ');
		h.setmapat(player1.getY(), player1.getX(), ' ');
		switch (numGhosts) {
		case 2: Tinky_Winky.display(h.getmapat(Tinky_Winky.getY(), Tinky_Winky.getX()));
		case 1: Po.display(h.getmapat(Po.getY(), Po.getX()));
		}
		checkInput = false;

		if (_kbhit())
			key1 = _getch();

		while (checkInput == false) {
			if (key1 == ESC) {
				h.pause(h);
				player1.display();
				Tinky_Winky.display();
				Po.display();
				short flag;
				flag = _getch();
				while (flag != ESC)
					flag = _getch();
				Tinky_Winky.display(h.getmapat(Tinky_Winky.getY(), Tinky_Winky.getX()));
				Po.display(h.getmapat(Po.getY(), Po.getX()));
				key1 = key2;
				h.unpause(h);
			}

			else if (key1 == 'w' || key1 == 'W')
				player1.move_up(h);
			else if (key1 == 'x' || key1 == 'X')
				player1.move_down(h);
			else if (key1 == 'a' || key1 == 'A')
				player1.move_left(h);
			else if (key1 == 'd' || key1 == 'D')
				player1.move_right(h);
			else if (key1 == 's' || key1 == 'S')
				player1.stop(h);
			else {
				key1 = key2;
				continue;
			}
			checkInput = true;
		}

		key2 = key1;
		player1.displayPoints(h);

		if (player1.getDotsate() == 493) {
			clearScreen();
			displaywin();
			running1 = false;
			running2 = false;
			break;
		}

		player1.display();
		dest = make_pair(player1.getY(), player1.getX());
		if (frame % ghostspeed == 0) {
			switch (numGhosts) {
			case 2:
				//Tinky_Winky.move_rand(h);
				src = make_pair(Tinky_Winky.getY(), Tinky_Winky.getX());
				if (dest == src)
					break;
				move = aStarSearch(h.board, src, dest);
				nextY = (short)move.first;
				nextX = (short)move.second;
				Tinky_Winky.move(nextX, nextY);
			case 1:
				//Po.move_rand(h);
				src = make_pair(Po.getY(), Po.getX());
				if (dest == src)
					break;
				move = aStarSearch(h.board, src, dest);
				nextY = (short)move.first;
				nextX = (short)move.second;
				Po.move(nextX, nextY);
			}
		}
		switch (numGhosts) {
		case 2: Tinky_Winky.display();
		case 1: Po.display();
		}

		if ((Tinky_Winky.getX() == player1.getX() && Tinky_Winky.getY() == player1.getY()) || (Po.getX() == player1.getX() && Po.getY() == player1.getY()))
		{
			player1.setLives(player1.getLives() - 1);
			Sleep(4000);
			player1.displayLives(h);
			key1 = 's';
			player1.reset();
			switch (numGhosts) {
			case 2:
				Tinky_Winky.display(h.getmapat(Tinky_Winky.getY(), Tinky_Winky.getX()));
				Tinky_Winky.reset(15,7);
			case 1:
				Po.display(h.getmapat(Po.getY(), Po.getX()));
				Po.reset(30,7);
			}
			if (player1.getLives() == 0)
			{
				clearScreen();
				displaylose();
				running2 = false;
				running1 = false;
				break;
			}
		}
		Sleep(speed);
		frame++;
	}
	//}
	goToOption(0);
}



