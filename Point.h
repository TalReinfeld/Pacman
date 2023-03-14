#pragma once
#include <iostream>
#include<string>
#include <stdio.h>
#include <stdlib.h>
#include "GeneralFunc.h"
#include "constants.h"
using namespace std;

class Point {
	int y = 1;
	int x = 1;
	int maxRow;
	int maxCol ;
	int minRow=0;
public:
	Point(int _row=0,int _col=0, int _x = 1, int _y = 1) :x(_x), y(_y),maxRow(_row),maxCol(_col) {}
	inline int getX()const { return x; }
	inline int getY()const { return y; }
	void draw(char ch)const;
	void move(int direction, bool flag);
	int  moveRandom();
	void setXY(int _y, int _x);
	void setMaxRow(int _Maxrow) { maxRow = _Maxrow; }
	void setMaxCol(int _col) { maxCol = _col; }
};
