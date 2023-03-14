#pragma once
#include "Point.h"
#include "MovingObj.h"
class Ghost:public MovingObj {
	
public:
	Ghost(const int& Maxrow,const int& col, bool _silent):MovingObj(Maxrow,col,'$', _silent){}
	virtual ~Ghost(){}
	virtual void moveMovingObj(char ch)override ;
	
};