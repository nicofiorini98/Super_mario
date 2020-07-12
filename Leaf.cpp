#include "Mario.h"
#include "Sounds.h"
#include "Sprites.h"
#include "Leaf.h"
#include <iostream>

Leaf::Leaf(QPoint position) : Collectable(position)
{
	// set attributes
	falling_speed_div = 1;
	falling = false;
	
	moving_speed_div = 1;
	setPixmap(Sprites::instance()->get("leaf"));
	setPos(position);
	Sounds::instance()->play("spawn");
}

void Leaf::animate()
{
	Entity::animate();
	
	if(dir==LEFT)
		setPixmap(Sprites::instance()->get("leaf"));
	else
		setPixmap(Sprites::instance()->get("leaf").transformed(QTransform().scale(-1, 1)));
}

void Leaf::hit(Object* what, Direction fromDir)
{
	Object::hit(what, fromDir);

	Mario* mario = dynamic_cast<Mario*>(what);
	if (mario)
	{
		mario->powerUp(LEAF);
		mario->updateScore(1000, pos().toPoint());
		die();
	}
}

void Leaf::advance()
{
	if (dir == UP) 
	{
		if (y() == spawned_position.y() - 3 * pixmap().height() + 16)
			moving_speed_div = 2;
		if (y() == spawned_position.y() - 3 * pixmap().height() + 12)
			moving_speed_div = 3;
		if (y() == spawned_position.y() - 3 * pixmap().height() + 8)
			moving_speed_div = 4;
		if (y() == spawned_position.y() - 3 * pixmap().height() + 4)
			moving_speed_div = 5;
		if (y() == spawned_position.y() - 3 * pixmap().height()) {
			falling = true;
			collidable = true;
			dir = RIGHT;
		}
	}
	falling_speed = animation_counter % falling_speed_div == 0;

	if (falling && falling_counter < 3)
		falling_speed_div = 1;

	if (falling_counter >= 3 && falling_counter < 6)
		moving_speed_div = 4;

	if (falling_counter >= 6 && falling_counter < 9)
		moving_speed_div = 3;

	if (falling_counter >= 9 && falling_counter < 12)
		moving_speed_div = 2;

	if (falling_counter >= 12 && falling_counter < 15)
		moving_speed_div = 1;


	if (falling_counter >= 15 && falling_counter < 18)
		falling_speed_div = 2;

	if (falling_counter >= 18 && falling_counter < 21)
		falling_speed_div = 3;

	if (falling_counter >= 21 && falling_counter < 24)
		falling_speed_div = 4;

	if (falling_counter >= 24 && falling_counter < 27)
		falling_speed_div = 5;

	if (falling_counter >= 27 && falling_counter < 30)
	{
		falling_speed = -(animation_counter % falling_speed_div == 0);
		falling_speed_div = 4;
	}
	if (falling_counter >= 30 && falling_counter < 36)
	{
		falling_speed = -(animation_counter % falling_speed_div == 0);
		falling_speed_div = 3;
	}
	if (falling_counter >= 36 && falling_counter < 42)
	{
		falling_speed = -(animation_counter % falling_speed_div == 0);
		falling_speed_div = 2;
	}
	if (falling_counter == 42)
	{
		dir = inverse(dir);
		falling_counter = 0;
	}

	
	Entity::advance();
}