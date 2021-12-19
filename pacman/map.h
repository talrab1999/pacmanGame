#pragma once

#include <Windows.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "color.h"
using namespace std;
#define ROWS 20
#define COLS 61

class map {
private:
	short width, height, length, dotCounter;
	string filename;
	vector<char> map_vec;

public:
	char board[ROWS][COLS];
	map(string mapNum="1");
	void gotoxy(short, short) const;
	short getWidth() const;
	void setWidth(short);
	short getHeight() const;
	void setHeight(short);
	short getLength() const;
	char getmapat(short, short) const; 
	void setFilename(string);
	void setmapat(short, short, char);
	void fillmap();
	void freemap();
	void ResetMap();
	void ShowMap();
	short getDots();
	void setDots(short);
	void pause(map&,int,int);
	void unpause(map&, int, int);
	string getFilename() const;
};
