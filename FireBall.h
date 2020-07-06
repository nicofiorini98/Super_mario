#pragma once
#include "Entity.h"
#include "Enemy.h"

class FireBall :public Entity
{
protected:
	// animation divisors
	int animation_div;
	QPixmap texture_rotate[4];
	QPixmap texture_boom[3];// brown/red walk animation
	bool script_move;
	
	
public:

	FireBall(QPoint position, Direction direction);
	
	// pure virtual methods that must be implemented
	virtual std::string name() { return "FireBall"; }
	virtual void animate();
	virtual void hit(Object* what, Direction fromDir);
	virtual void advance();
	
};