#pragma once
#include "Game.h"
#include "BouncingBlock.h"
#include "Mushroom.h"
#include "Mario.h"
class JumpBlock : public BouncingBlock
{
protected:
	Mario* mario;
	

	QPoint pos_in;
	QPixmap texture_animation[3];
	int hit_start_counter;
	int hit_duration;

public:

	JumpBlock(QPoint position);

	virtual std::string name() { return "JumpBlock"; }
	virtual void animate();
	virtual void advance();
	virtual void hit(Object* what, Direction fromDir);
};