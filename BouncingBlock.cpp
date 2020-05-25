#include "BouncingBlock.h"
#include "Sounds.h"
#include "SwitchBlock.h"
#include "BrickBlock.h"
//#include "Mushroom.h"
//#include "Flower.h"
//#include "Leaf.h"

BouncingBlock::BouncingBlock() : Inert()
{

	// attributes
	dir = UP;
	active = true;
	mario = 0;
	moving = false;
	moving_speed = 1;
	hit_counter = -1;
	//content = FLOWER;
}

void BouncingBlock::advance()
{

	if (moving)
	{
		if (dir == UP)
			setY(y() - moving_speed);
		else if (dir == DOWN)
			setY(y() + moving_speed);
	}
}

void BouncingBlock::hit(Object* what, Direction fromDir)
{
	// do nothing if not active
	if (!active)
		return;

	mario = dynamic_cast<Mario*>(what);
	if (mario && fromDir == DOWN)
	{
		// start hit
		hit_counter = 0;

		// disable box
		active = false;

		if (dynamic_cast<BrickBlock*>(this))
			new SwitchBlock(QPoint(pos().x(),pos().y()-16));
			
		moving = true;

		// play box hit sound
		Sounds::instance()->play("bump");
	}
}


void BouncingBlock::spawn()
{
	if (content == FLOWER)
	{
		if (mario->isBig())
			;   // spawn flower object
		else
			new Mushroom(QPoint(x(), y()), UP, true);
	}	
	else if (content == LEAF)
	{
		if (mario->isBig())
			;	// spawn leaf object
		else
			new Mushroom(QPoint(x(), y()), UP, true);
	}
	else if (content == LIFE)
		new Mushroom(QPoint(x(), y()), UP, false);
}
