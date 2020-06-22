#pragma once
#include "Game.h"
#include "BouncingBlock.h"
#include "Mushroom.h"
#include "Mario.h"
class JumpBlock : public BouncingBlock
{
protected:
	Mario* mario;

	bool down;
	bool up;

	QPoint pos_in;
	QPixmap texture_animation[3];
	int hit_start_counter;
	int hit_duration;

public:

	JumpBlock(QPoint position);
	bool isUp() { return up; }
	bool isDown() { return down; }

	virtual std::string name() { return "JumpBlock"; }
	virtual void animate();
	virtual void advance();
	virtual void hit(Object* what, Direction fromDir);
};