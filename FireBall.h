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
	bool up_mario;
	bool left_mario;
	bool enemy;
	
public:

	FireBall(QPoint position, Direction direction, bool _enemy, bool mario_up);
	bool get_enemy() { return enemy; }
	// pure virtual methods that must be implemented
	virtual std::string name() { return "Fire_Ball"; }
	virtual void animate();
	virtual void hit(Object* what, Direction fromDir);
	virtual void advance();
	// enemies can be hurt
	virtual void hurt();
};