#pragma once
#include "Plant.h"


class Piranha : public Plant
{
protected:
	bool rotate;
	bool red;
	// textures
	QPixmap texture_crunch[2];	

	QPoint pos_in;


public:

	Piranha(QPoint position, Direction direction, bool _red, bool _rotate=false);
	// pure virtual methods that must be implemented
	virtual std::string name() { return "piranha"; }
	virtual void advance();

	virtual void animate();
	virtual void hit(Object* what, Direction direction);
	virtual void hurt();
	
};
