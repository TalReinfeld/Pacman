#pragma once
#include "Point.h"
#include "MovingObj.h"
class Pacman :public MovingObj {
	enum { keyBoardSize = 6 };
	int direction = (int)Directions::STAY;
	char arrowKeys[keyBoardSize] = "wxads";
public:
	Pacman(const int& Maxrow,const int& col, bool _silent):MovingObj(Maxrow, col, '@', _silent) {}
	virtual ~Pacman() override{}
	virtual void  moveMovingObj(char ch)override;
	int getDirection(char key)const;
	void setDirection(const int& dir);
	void updateEyes(int dir);
	int getDirection() { return direction; }
};