#pragma once

#include "Entity.h"

class Firework : Entity
{
private:

	//std::string type;
	QPixmap texture_animation[3];

public:

	Firework(QPoint position, const std::string& type);

	virtual std::string name() { return "Firework"; }
	virtual void animate();
	virtual void hit(Object *what, Direction fromDir){/*do nothing*/}
};