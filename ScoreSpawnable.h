#pragma once
#include "Entity.h"

class ScoreSpawnable : public Entity
{
protected:

	// textures
	QPixmap texture;

public:

	ScoreSpawnable(QPoint position,std::string id);

	// inherited methods
	virtual std::string name() { return "ScoreSpawnable";}
	virtual void animate();
	virtual void hit(Object* what, Direction fromDir) {}

	// @override
	virtual void advance();
};