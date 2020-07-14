#include "Mushroom.h"
#include "Mario.h"
#include "Sounds.h"
#include "Sprites.h"
#include <iostream>
#include "Iceberg.h"

Mushroom::Mushroom(QPoint position, Direction _dir, bool _red) : Collectable(position)
{
	// set attributes
	red = _red;
	dir = _dir;
	if (red)
		type = MUSHROOM;
	else
		type = LIFE;

	moving_counter = 0;
	falling_speed = 2;

	// set texture and position
	setPixmap(Sprites::instance()->get(red ? "mushroom-red" : "mushroom-green"));
	setPos(position);
	setZValue(1);
	// play mushroom sound
	Sounds::instance()->play("spawn");
}


void Mushroom::animate()
{
	Entity::animate();

	
}

void Mushroom::hit(Object* what, Direction fromDir)
{
	Object::hit(what, fromDir); 

	//walking phase on uphill or downhill
	if (dynamic_cast<Iceberg*>(what) && dynamic_cast<Iceberg*>(what)->type() == "downhill")
	{
		falling = false;
		script_move = true;
		downhill = true;
	}
	else if (dynamic_cast<Iceberg*>(what) && dynamic_cast<Iceberg*>(what)->type() == "uphill")
	{
		falling = false;
		script_move = true;
		downhill = false;
	}
	else
		script_move = false;

	
	// if hit by Mario, Mario eats mushroom and mushroom dies
	Mario* mario = dynamic_cast<Mario*>(what);
	if (mario)
	{
		//if mushroom is red mario becomes big
		if(red)
			mario->powerUp(type);
		//if mushroom is green mario gains a new life
		if(type==LIFE)
		{
			mario->updateLives(1, pos().toPoint());
			Sounds::instance()->play("1up");
		}
		else 
			mario->updateScore(1000,pos().toPoint());
		die();
		return;
	}

	Inert* inert_obj = dynamic_cast<Inert*>(what);
	if (inert_obj && fromDir == DOWN)
		walkable_object = inert_obj;

	// if hit from its left or right side, it
	// has to move to the opposite direction w.r.t. the one
	// is he currently moving
	if (fromDir == RIGHT || fromDir == LEFT)
		setDirection(inverse(dir));
}

void Mushroom::advance()
{
	//raising phase from the block
	if (dir == UP)
	{
		collidable = true;
		if (y() >= spawned_position.y() - pixmap().height())
		{
			setY(y() - moving_speed);
		}
		if (y() < spawned_position.y() - pixmap().height())
		{
			if (type == LIFE)
			{
				jumping = true;
				jumping_duration = 60;
			}
			else
				falling = true;
			

			slow = false;
			moving_speed = 1;
			dir = RIGHT;
		}
	}

	//falling phase from the block
	else if (dir == DOWN) {
		slow = false;
		falling = true;

		if (y() >= spawned_position.y() + pixmap().height() + 16) {
			collidable = true;
			moving_speed = 1;
		}
		if (walkable_object)
		{
			dir = RIGHT;
		}

	}
	else
		Entity::advance();

	
}
