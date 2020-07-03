#include "FireBall.h"
#include "Sprites.h"
#include <iostream>
#include "Iceberg.h"

FireBall::FireBall(QPoint position, Direction direction, bool _enemy, bool mario_up) {

	script_move = false;
	dir = direction;
 	animation_div    = 10;
 	moving_speed_div = 2;
 	moving_speed=2;
	moving = true;
	// durations
	death_duration = 15;
	
	enemy = _enemy;
	up_mario = mario_up; // ? da aggiustare questo mario_up che serve per la fireball della pianta
						 // si pu? fare in un altra maniera con il puntatore della pianta penso

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
	if (!enemy) 	
	{
		std::cout << script_move << "\n";
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
		if(jumping)
		{
			if (jump_counter <= jumping_duration / 2)
				jumping_speed = 3;
			else if (jump_counter > jumping_duration / 2 && jump_counter < jumping_duration - 4)
				jumping_speed = 2;
			else
				jumping_speed = 1;
		}
		if(falling)
		{
			//falling accelleration
			if (falling_counter < 2)
				falling_speed = 1;
			else if (falling_counter >= 2 && falling_counter < 6)
				falling_speed = 2;
			else
				falling_speed = 3;
		}


	}
	else
    {
		//todo vedere un po' come posso fare altrimenti, ? la pianta che deve gestire mario
		//da cambiare up_mario, credo serve per dire che mario sta in alto rispetto alla pianta
		if (up_mario && dir == LEFT)
		{
			setY(y() - 1 - (moving_speed / moving_speed_div) % 2);
			setX(x() - moving_speed);
		}
		else if (up_mario && dir == RIGHT)
		{
			setY(y() - 1 - (moving_speed / moving_speed_div) % 2);
			setX(x() + moving_speed);
		}
		else if (!up_mario && dir == RIGHT)
		{
			setY(y() + 1 + (moving_speed / moving_speed_div) % 2);
			setX(x() + moving_speed);
		}
		else if (!up_mario && dir == LEFT)
		{
			setY(y() + 1 + (moving_speed / moving_speed_div) % 2);
			setX(x() - moving_speed);
		}
    }
	Entity::advance();
}

void FireBall::hit(Object* what, Direction fromDir)
{
	//when fireball hit from right or left, then dying
	if ((dynamic_cast<Inert*>(what) && (fromDir!=DOWN && fromDir != UNDETERMINED && fromDir != UP)) || dynamic_cast<Enemy*>(what))
		dying = true;

	//when hit with downhill or uphill, paramenters will change
	if (dynamic_cast<Iceberg*>(what) && ((dynamic_cast<Iceberg*>(what)->type() == "downhill") || dynamic_cast<Iceberg*>(what)->type() == "uphill"))
		script_move = true;
	else
		script_move = false;
}

void FireBall::hurt()
{
	/*do nothing*/
}