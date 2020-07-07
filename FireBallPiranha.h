#pragma once
#include "Enemy.h"

class FireBallPiranha :public Enemy
{
protected:
	
	QPixmap texture[4];

	int angle_dir; //angle from the x-axis

public:

	FireBallPiranha(QPoint position, Direction direction, int _angle_dir = 30);
	
	// pure virtual methods that must be implemented
	virtual std::string name() { return "FireBallPiranha"; }
	virtual void animate();
	virtual void hit(Object* what, Direction fromDir){}
	virtual void advance();
	
	virtual void hurt(){}
};