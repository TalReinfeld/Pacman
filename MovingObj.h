#pragma once
#include "Point.h"
class MovingObj {
protected:
	Point body;
	Point Eyes;
	char figure;
	bool color = false;
	string moves;
	int place = 0;
	bool silent = false;
public:
	MovingObj(bool _silent):silent(_silent){}
	MovingObj(const int& Maxrow, const int& col,char _figure, bool _silent):body(Maxrow, col), Eyes(Maxrow, col), figure(_figure), silent(_silent){}
	void setMovingObjColor(bool _color);
	virtual void moveMovingObj(char ch);
	virtual ~MovingObj() {}
	void drawMovingObj();
	inline int getMovingObjBodyX()const { return body.getX(); }
	inline int getMovingObjBodyY()const { return body.getY(); }
	inline int getMovingObjEyesX()const { return Eyes.getX(); }
	inline int getMovingObjEyesY()const { return Eyes.getY(); }
	int updateEyes();
	void continueOldDir(const int& dir);
	void setEyesLocation(int y, int x);
	void initLocation(const int& y, const int& x);
	void UpdateBorders(int _Maxrow, int MaxCol);
	void addMove(char dir) { moves.push_back(dir); }
	char readMove();
	void addTime(int time);
	int getPlace() { return place; }
	char giveMeTheDir() { return moves[getPlace()]; }
	void changePlace(int i = 1);
	void oneStepBack() { place--; }
	inline string& myMoves() { return moves; }
	void restartObj() { moves.clear(); changePlace(0); }
	string convertNum(int num);
	void fillString(string& str);
};