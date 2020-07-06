#include "FireBall.h"
#include "Sprites.h"
#include <iostream>
#include "Iceberg.h"

FireBall::FireBall(QPoint position, Direction direction) {

	script_move = false;
	dir = direction;
 	animation_div    = 10;
 	moving_speed_div = 2;
 	moving_speed=2;
	moving = true;
	// durations
	death_duration = 15;
	
	// textures
	texture_rotate[0] = Sprites::instance()->get("fire-ball-left-0");
	texture_rotate[1] = Sprites::instance()->get("fire-ball-left-1");
	texture_rotate[2] = Sprites::instance()->get("fire-ball-left-2");
	texture_rotate[3] = Sprites::instance()->get("fire-ball-left-3");
	texture_boom[0] = Sprites::instance()->get("boom-0");
	texture_boom[1] = Sprites::instance()->get("boom-1");
	texture_boom[2] = Sprites::instance()->get("boom-2");
	
	setPixmap(texture_rotate[0]);
	setPos(position - QPoint(0, pixmap().height()));
	setZValue(2);
	
}

void FireBall::animate()
{
	Entity::animate();
	
	if (!dying)
	{
		if (dir == LEFT)
			setPixmap(texture_rotate[(animation_counter / animation_div) % 4]);

		else if (dir == RIGHT)
			setPixmap(texture_rotate[(animation_counter / animation_div) % 4].transformed(QTransform().scale(-1, 1)));
	}
	else 
		setPixmap(texture_boom[(death_counter / 5) % 3]);
}


void FireBall::advance()
{
	//fire ball shoot by mario

	//std::cout << script_move << "\n";
	if (freezed || dying)
		return;

	if (walkable_object)
	{
		jumping = true;
		walkable_object = nullptr;
	}

	if (script_move)
	{
		jumping_duration = 80;
		moving_speed = 2;
	}
	else
	{
		jumping_duration = 20;
		moving_speed = 3;
	}
	//jumping accelleration
	if (jumping)
	{
		if (jump_counter <= jumping_duration / 2)
			jumping_speed = 3;
		else if (jump_counter > jumping_duration / 2 && jump_counter < jumping_duration - 4)
			jumping_speed = 2;
		else
			jumping_speed = 1;
	}
	if (falling)
	{
		//falling accelleration
		if (falling_counter < 2)
			falling_speed = 1;
		else if (falling_counter >= 2 && falling_counter < 6)
			falling_speed = 2;
		else
			falling_speed = 3;
	}
	Entity::advance();
}

void FireBall::hit(Object* what, Direction fromDir)
{
	//when hit from right or left, then die
	if ((dynamic_cast<Inert*>(what) && (fromDir!=DOWN && fromDir != UNDETERMINED && fromDir != UP)) || dynamic_cast<Enemy*>(what))
		dying = true;

	//when hit with downhill or uphill, paramenters will change
	if (dynamic_cast<Iceberg*>(what) && ((dynamic_cast<Iceberg*>(what)->type() == "downhill") || dynamic_cast<Iceberg*>(what)->type() == "uphill"))
		script_move = true;
	else
		script_move = false;

	//hurt enemy if hittedd and dying
	Enemy* enemy = dynamic_cast<Enemy*>(what);
	if (dynamic_cast<Enemy*>(what))
	{
		dying = true;
		enemy->hurt();
	}
}
