#pragma once

#include <Windows.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "color.h"
using namespace std;
#define ROWS 19
#define COLS 61

class map {
private:
	short width, height, length, dotCounter;
	string filename;
	vector<char> map_vec;

public:
	map();
	char board[ROWS][COLS];
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
	void ResetMap();
	void ShowMap();
	short getDots();
	//testing
	void test();
	void fillboard();
	//testing
	void pause(map&);
	void unpause(map&);
	string getFilename() const;
};
