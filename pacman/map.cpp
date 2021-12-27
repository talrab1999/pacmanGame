
#include "map.h"

map::map(string mapNum)
{
	/*width = COLS;
	height = ROWS;
	length = width * height;*/
	dotCounter = 0;
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
	//resetBoard
	setDots(0);
	map_vec.clear();
	ifstream INF(filename);
	string line = "";
	if (!INF) {
		cout << "ERROR map" << filename << ".screen COULD NOT BE OPENED!";
	}
	int z = 0;
	bool isLegends = false;
	int legendCounter = 0;
	int legendIndex = 81;
	while (getline(INF, line)) {
		if (z == 0) {
			width = line.size() + 1;
		} 
		// for loop fixes the line
		fixLine(legendIndex, legendCounter, line);
		for (int j = 0; j < width; j++) {
			board[z][j] = line[j];
		}
		for (short i = 0; i < width; i++) {
			if (line[i] == '%' || line[i] == '@')
				line[i] = ' ';
			else if (line[i] == '$') {
				line[i] = '.';
			}
			else if (line.size() == 1) {
				for (int i = 0; i < 3 * 20; i++) {
					map_vec.push_back(' ');
				}
				i = width;
				continue;
			}
			map_vec.push_back(line[i]);
		}
		z++;
	}
	height = z;  
	length = width * height;
	INF.close();
}

void map::fixLine(int& legendIndex, int& legendCounter, string& line) {
	for (short i = 0; i < width; i++) {
		if (legendCounter && legendIndex == i) {
			for (i; i < legendIndex + 20; i++)
				line[i] = '%';
			
			legendCounter++;
			if (legendCounter == 3)
				legendCounter = 0;
		}
		if (line[i] == '&') {
			if (line.size() == 1) {
				legendIndex = i;
				return;
			}
			legendIndex = i;
			i++;
			for (i; i <= legendIndex + 19; i++) {
				line[i] = '%';
			}

			legendCounter = 1;
		}
		if (line[i] == ' ') {
			line[i] = '.';
			dotCounter++;
		}
	}
}

//void map::fillmap()
//{
//	//resetBoard
//	setDots(0);
//	map_vec.clear();
//	ifstream INF(filename);
//	string line = "";
//	if (!INF) {
//		cout << "ERROR map" << filename << ".screen COULD NOT BE OPENED!";
//	}
//	int z = 0;
//	while (getline(INF, line)) {
//		if (z == 0) {
//			width = line.size() + 1;
//		}
//		for (short i = 0; i < width; i++) {
//			if (line[i] == ' ') {
//				line[i] = '.';
//				dotCounter++;
//			}
//			if (line[0] == '&') {
//				i = width;
//			}
//		}
//		for (int j = 0; j < width; j++) {
//			if (line[0] == '&') {
//				board[z][j] = '&';
//				j = width;
//			}
//			else
//				board[z][j] = line[j];
//		}
//		for (short i = 0; i < width; i++) {
//			if (line[i] == '%' || line[i] == '@')
//				line[i] = ' ';
//			else if (line[i] == '$') {
//				line[i] = '.';
//			}
//			else if (line[i] == '&') {
//				for (int i = 0; i < 3 * 20; i++) {
//					map_vec.push_back(' ');
//				}
//				i = width;
//				continue;
//			}
//			map_vec.push_back(line[i]);
//		}
//		z++;
//	}
//	height = z;
//	length = width * height;
//	INF.close();
//}

void map::freemap() {
	map_vec.clear();
}

short map::getDots() {
	return dotCounter;
}

void map::setDots(short) {
	dotCounter = 0;
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


void map::pause(map& h,int x,int y) {
	gotoxy(0,y + 2);
	cout << "Game paused" << endl;
}

void map::unpause(map& h, int x, int y) {
	gotoxy(x, y+2);
	cout << "               " << endl;
}