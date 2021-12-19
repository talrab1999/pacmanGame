
#include "map.h"

map::map(string mapNum)
{
	width = 61;
	height = 19;
	dotCounter = 0;
	length = width * height;
	setFilename(mapNum);
}

void map::gotoxy(short i, short j) const
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { i, j };
	SetConsoleCursorPosition(hStdout, position);
}

short map::getWidth() const
{
	return width;
}

short map::getHeight() const
{
	return height;
}

short map::getLength() const
{
	return length;
}

string map::getFilename() const
{
	return filename;
}

char map::getmapat(short y, short x) const
{
	return map_vec[x + width * y];
}

void map::setWidth(short w)
{
	width = w;
}

void map::setHeight(short h)
{
	height = h;
}

void map::setFilename(string mapNum)
{
	filename = "map" + mapNum + ".screen";
}

void map::setmapat(short y, short x, char c) {
	map_vec[x + width * y] = c;
}

void map::fillmap()
{
	setDots(0);
	map_vec.clear();
	ifstream INF(filename);
	string line = "";
	if (!INF) {
		cout << "ERROR map" << filename << ".screen COULD NOT BE OPENED!";
	}
	int z = 0;
	while (getline(INF, line)) {
		for (short i = 0; i < width; i++) {
			if (line[i] == ' ') {
				line[i] = '.';
				dotCounter++;
			}
		}
		for (int j = 0; j < width; j++) {
			board[z][j] = line[j];
		}
		for (short i = 0; i < width; i++) {
			if (line[i] == '%' || line[i] == '@')
				line[i] = ' ';
			else if (line[i] == '$') {
				line[i] = '.';
				dotCounter++;
			}
			map_vec.push_back(line[i]);
		}
		z++;
	}
	INF.close();
}

void map::freemap() {
	map_vec.clear();
}

short map::getDots() {
	return dotCounter;
}

void map::setDots(short) {
	dotCounter = 0;
}


void map::test() {
	gotoxy(0, 0);
	for (int i = 0; i < height; i++) {
		printf("\n");
		for (int j = 0; j < width; j++) {
			cout << board[i][j];
		}
	}

}

void map::ResetMap()
{
	map_vec.clear();
	gotoxy(0, 0);
	fillmap();
}

void map::ShowMap()
{
	for (short i = 1; i <= length; i++)
	{

		if (i % width == 0)
		{
			//setTextColor(BLUE);
			cout << "\n";
		}
		else
		{
			/*if(map_vec[i - 1] == '#')
				setTextColor(BLUE);
			else
				setTextColor(WHITE);*/
			cout << map_vec[i - 1];
		}

	}
}


void map::pause(map& h) {
	gotoxy(0, h.getHeight() + 1);
	cout << "Game paused, press ESC again to continue" << endl;
}

void map::unpause(map& h) {
	gotoxy(0, h.getHeight() + 1);
	cout << "                                           " << endl;
}