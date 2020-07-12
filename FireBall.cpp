#include "FireBall.h"
#include "Sprites.h"
#include <iostream>
#include "Iceberg.h"
#include "BlooberBaby.h"

FireBall::FireBall(QPoint position, Direction direction) {

	//set default flags
	script_move = false;
	moving = true;
	
	dir = direction;
	moving_speed = 2;
	
	// set durations
	death_duration = 15;
	
	// textures
	texture[0] = Sprites::instance()->get("fire-ball-left-0");
	texture[1] = Sprites::instance()->get("fire-ball-left-1");
	texture[2] = Sprites::instance()->get("fire-ball-left-2");
	texture[3] = Sprites::instance()->get("fire-ball-left-3");
	texture_dying[0] = Sprites::instance()->get("boom-0");
	texture_dying[1] = Sprites::instance()->get("boom-1");
	texture_dying[2] = Sprites::instance()->get("boom-2");
	
	setPixmap(texture[0]);
	setPos(position - QPoint(0, pixmap().height()));
	setZValue(2);
	
}

void FireBall::animate()
{
	Entity::animate();
	
	if (!dying)
	{
		if (dir == LEFT)
			setPixmap(texture[(animation_counter / 10) % 4]);

		else if (dir == RIGHT)
			setPixmap(texture[(animation_counter / 10) % 4].transformed(QTransform().scale(-1, 1)));
	}
	else 
		setPixmap(texture_dying[(death_counter / 5) % 3]);
}


void FireBall::advance()
{
	//fire ball shoot by mario

	//don't advance when dying or freezed
	if (freezed || dying)
		return;

	//start jumping when hit with walkable_object
	if (walkable_object)
	{
		jumping = true;
		walkable_object = nullptr;
	}

	//different physic parameter between horizontal walkable_object
	//and uphill or downhill walkable_object
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
	
	//set the proper speed during the jumping
	if (jumping)
	{
		if (jump_counter <= jumping_duration / 2)
			jumping_speed = 3;
		else if (jump_counter > jumping_duration / 2 && jump_counter < jumping_duration - 4)
			jumping_speed = 2;
		else
			jumping_speed = 1;
	}
	
	//set the proper falling_speed during the falling
	if (falling)
	{
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
	
	if (dynamic_cast<FireBall*>(what))
	{
		dying = true;
	}
		
	//hurt enemy if hittedd and dying
	Enemy* enemy = dynamic_cast<Enemy*>(what);
	if (dynamic_cast<Enemy*>(what) )
	{
		dying = true;
		enemy->hurt();
		return;
	}

	//when hit from right or left, then die
	if ((dynamic_cast<Inert*>(what) && (fromDir != DOWN && fromDir != UNDETERMINED && fromDir != UP)) || dynamic_cast<Enemy*>(what))
		dying = true;

	//when hit with downhill or uphill, paramenters will change
	if (dynamic_cast<Iceberg*>(what) && ((dynamic_cast<Iceberg*>(what)->type() == "downhill") || dynamic_cast<Iceberg*>(what)->type() == "uphill"))
		script_move = true;
	else
		script_move = false;

}
