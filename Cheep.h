#pragma once
#include "Enemy.h"

class Cheep : public Enemy
{
protected:

	// attributes
	bool red;

	// textures
	QPixmap texture_swim[2];		// brown/red walk animation
	QPixmap texture_death;		    // brown/red smashed texture
	QPoint pos_in;

public:

	Cheep(QPoint position, Direction direction = LEFT);

	// pure virtual methods that must be implemented
	virtual std::string name() { return "Cheep"; }
	virtual void animate();
	virtual void hit(Object* what, Direction fromDir);
	virtual void hurt();
	virtual void advance();
};