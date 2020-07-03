#pragma once
#include "Enemy.h"
#include "Mario.h"
#include "FireBall.h"

class PlantFire : public Enemy
{
private:
	//int moving_start_counter;
	int out_counter;
	int in_counter;
protected:
	Mario* mario;
	bool active;
	bool mario_up;
	bool mario_left;
	bool in;


	// textures
	QPixmap texture_crunch_down[2];		// brown/red walk animation
	QPixmap texture_crunch_up[2];		// brown/red walk animation

	QPoint pos_in;
	FireBall* f;

public:

	PlantFire(QPoint position, Direction direction);
	// pure virtual methods that must be implemented
	virtual std::string name() { return "PlantFire"; }
	virtual void advance();

	virtual void animate();
	virtual void hit(Object* what, Direction direction);
	virtual void hurt();

};