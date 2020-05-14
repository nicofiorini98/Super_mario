#pragma once

#include "Entity.h"
#include "Sprites.h"
#include <iostream>




class Splash : public Entity
{
protected:
	
	QPixmap texture_splash[5];
	int animation_div;
public:

	Splash(QPointF _pos);
	QPointF pos;

	// inherited methods
	virtual std::string name() { return "Splash"; }
	void animate();
	
	virtual void hit(Object* what, Direction fromDir) { /* do nothing */ };
}; 