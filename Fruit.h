#pragma once
#include "Point.h"
#include "MovingObj.h"
class Fruit:public MovingObj {
	int timeToApear;
	bool lifeSwitch = false;
	
public:
	Fruit(bool _silent);
	virtual ~Fruit()override{}
	inline int getFigure() { return figure - '0'; }
	void setFigure(int num) { figure = num + '5'; }
	virtual void moveMovingObj(char ch)override;

	inline int getTimeTo() { return timeToApear; }
	void changeTimeTo(int newTime) { timeToApear = newTime; }
	void writeTimeTo();
	inline bool getLifeSwitch() { return lifeSwitch; }
	void changeSwitch() { lifeSwitch = !lifeSwitch; }
	void addCoord(int y, int x);
	int readCoord();
};