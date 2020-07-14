#include "Mario.h"
#include "Sounds.h"
#include "Flower.h"
#include "Sprites.h"
#include <iostream>
Flower::Flower(QPoint position, Direction _dir) : Collectable(position)
{
	// set attributes
	dir = _dir;      
	type = FLOWER;
	// set texture and position
	setPixmap(Sprites::instance()->get("flower"));
	setPos(position);
	setZValue(1);
	// play mushroom sound
	Sounds::instance()->play("spawn");
}

void Flower::animate()
{
	Entity::animate();


}

void Flower::hit(Object* what, Direction fromDir)
{
	Object::hit(what, fromDir);

	// if hit by Mario, Mario eats flower and flower dies
	Mario* mario = dynamic_cast<Mario*>(what);
	if (mario)
	{
		mario->powerUp(FLOWER);
		mario->updateScore(1000, pos().toPoint());
		die();
		return;
	}
	Inert* inert_obj = dynamic_cast<Inert*>(what);
	if (inert_obj && fromDir == DOWN)
		walkable_object = inert_obj;

	
}


void Flower::advance()
{
    //raising phase from the block
	if (dir == UP) 
	{
		collidable = true;
		setY(y() - moving_speed);
		if (y() == spawned_position.y() - pixmap().height())
		{

			falling = true;
			slow = false;
			moving = false;
		}
	}
	//falling phase from the block
	if (dir == DOWN) 
	{
		slow = false;
		falling = true;
		falling_speed = 2;
		if (y() >= spawned_position.y() + pixmap().height() + 16) {
			collidable = true;

		}
		if (walkable_object)
		{
			moving = false;
		}
	}

	Entity::advance();
}