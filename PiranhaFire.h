#pragma once
#include "Enemy.h"
#include "Mario.h"
#include "FireBallPiranha.h"
#include "Plant.h"

class PiranhaFire : public Plant
{
protected:
	
	Mario* mario;

	int angle;  
	//bool in;

	// textures
	QPixmap texture_crunch_down[2];		
	QPixmap texture_crunch_up[2];		
	//QPixmap texture_dying[12];		

	QPoint pos_in;
	FireBallPiranha* fire;

public:

	PiranhaFire(QPoint position, Direction direction);
	// pure virtual methods that must be implemented
	virtual std::string name() { return "piranhaFire"; }
	virtual void advance();

	virtual void animate();
	virtual void hit(Object* what, Direction direction);
	virtual void hurt();

};
