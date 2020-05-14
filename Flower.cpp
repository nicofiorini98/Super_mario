#include "Mario.h"
#include "Sounds.h"
#include "Flower.h"
#include "Sprites.h"
#include <iostream>
Flower::Flower(QPoint position, Direction _dir) : Collectable(position)
{
	// set attributes
	dir = _dir;      //todo deve essere istanziata o dall'alto o dal basso
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

	// if hit by Mario, Mario eats mushroom and mushroom dies
	Mario* mario = dynamic_cast<Mario*>(what);
	if (mario)
	{
		//todo aggiungere il powerUP
		//mario->powerUp(FLOWER);
		die();
		return;
	}
	Inert* inert_obj = dynamic_cast<Inert*>(what);
	if (inert_obj && fromDir == DOWN)
		walkable_object = inert_obj;

	// if hit from its left or right side, it
	// has to move to the opposite direction w.r.t. the one
	// is he currently moving
}


void Flower::advance()
{
	/*Entity::advance();*/
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