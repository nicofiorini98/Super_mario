#pragma once

#include "Entity.h"
#include <iostream>
class BrokenBlock : public Entity
{
protected:

	bool big_jump;                 //a broken block can do a big or a small jump
	QPixmap texture_broken[2];
	
	int duration;
public:

	BrokenBlock(QPointF _pos, Direction _dir, bool _big_jump);

	// pure virtual methods to be implemented
	virtual std::string name() { return "BrokenBlock"; }
	virtual void animate();
	virtual void advance();
	virtual void hit(Object* what, Direction fromDir) {}
	void setDuration(int _duration) { duration = _duration; }
};