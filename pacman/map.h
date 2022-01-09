#pragma once

#include <Windows.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define ROWS 25
#define COLS 80

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
	void fixLine(int&, int&, string&);
	void freemap();
	void ResetMap();
	void ShowMap();
	short getDots();
	void setDots(short);
	void pause(map&,int,int);
	void unpause(map&, int, int);
	string getFilename() const;
};
