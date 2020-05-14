#pragma once

#include "Collectable.h"

class Leaf : public Collectable
{
protected:

public:

	Leaf(QPoint position, Direction _dir);

	// inherited methods
	virtual std::string name() { return "Leaf"; }
	virtual void animate();
	virtual void advance();
	virtual void hit(Object* what, Direction fromDir);
	
};