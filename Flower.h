#pragma once

#include "Collectable.h"

class Flower : public Collectable
{
protected:


public:

	Flower(QPoint position, Direction _dir);

	// inherited methods
	virtual std::string name() { return "Flower"; }
	virtual void animate();
	virtual void advance();
	virtual void hit(Object* what, Direction fromDir);
};