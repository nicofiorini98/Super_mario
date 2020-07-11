#include "BouncingBlock.h"
#include "Sounds.h"
#include "SwitchBlock.h"
#include "BrickBlock.h"
#include "Mushroom.h"
#include "Flower.h"
#include "Leaf.h"
#include <iostream>
#include "Game.h"
//#include "Leaf.h"
//#include "Mushroom.h"
//#include "Flower.h"
//#include "Leaf.h"

BouncingBlock::BouncingBlock() : Inert()
{

	// attributes
	dir = UP;
	active = true;
	mario = Game::instance()->getMario();
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

//todo mesa devo passare come parametro anche la posizione dello spawn, visto che
//nella secretbox grande devo centrare di più rispetto alle altre
void BouncingBlock::spawn(Direction _dir)
{
	if (content == FLOWER)
	{
		if (mario->isBig())
		{
			new Flower(QPoint(x(), y()), _dir);   // spawn flower object
		}
		else
			new Mushroom(QPoint(x(), y()), _dir);
	}
	else if (content == LEAF)
	{
		if (mario->isBig())
			new Leaf(QPoint(x(),y()));	// spawn leaf object
		else
			new Mushroom(QPoint(x(), y()), _dir);
	}
	else if (content == LIFE)
		new Mushroom(QPoint(x(), y()), _dir, false);
	
}
