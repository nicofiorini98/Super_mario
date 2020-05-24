#pragma once

#include "Collectable.h"

class Leaf : public Collectable
{
protected:
	
	int falling_speed_div;

public:

	Leaf(QPoint position);

	// inherited methods
	virtual std::string name() { return "leaf"; }
	virtual void animate();
	virtual void advance();
	virtual void hit(Object* what, Direction fromDir);
};
