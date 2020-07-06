#include "PiranhaFire.h"
#include "Mario.h"
#include "Sprites.h"

#include "Sounds.h"
#include "Game.h"
#include <iostream>

PiranhaFire::PiranhaFire(QPoint position, Direction direction) : Enemy()
{
	in_counter = 0;
	out_counter = 0;
	in = true;
	falling_counter = 0;
	jump_counter = 0;
	angle = 30;

	// set attribute
	//mario = Game::instance()->getMario();
	mario = nullptr;

	pos_in = position;
	dir = direction;
	slow = true;  //boh po vedamo
	
	// animation divisor
	animation_div = 20;

	// durations
	death_duration = 100;

	// textures
	texture_crunch_up[0] = Sprites::instance()->get("plant-fire-up-0");
	texture_crunch_up[1] = Sprites::instance()->get("plant-fire-up-1");

	texture_crunch_down[0] = Sprites::instance()->get("plant-fire-down-0");
	texture_crunch_down[1] = Sprites::instance()->get("plant-fire-down-1");


	setPixmap(texture_crunch_up[0]);

	setPos(position - QPoint(0, pixmap().height()));
	setZValue(2);
}


void PiranhaFire::advance()
{

	if(mario !=nullptr)
	{
		if (mario->pos().y() <= pos().y() - 10)
			angle = 30;
		else if (mario->pos().y() <= pos().y() + 10)
			angle = -30;
		else
			angle = -45;

		//when mario goes out of sight of the piranha, then piranha is freezed
		if ((mario->pos().x() >= pos().x() + 16 * 16 || mario->pos().x() <= pos().x() - 16 * 16) 
			|| (mario->pos().y() >= pos().y() + 10 * 16 || mario->pos().x() <= pos().x() - 12 * 16))
			freezed = true;
		else
			freezed = false;
		


		if (mario->pos().x() >= pos().x() + boundingRect().width() / 2)
			dir = RIGHT;
		else
			dir = LEFT;
	}
	
;
	
	if (freezed)
		return;
	
	if (in)
	{
		
		if (falling_counter >= 0)
			falling_counter++;

		if (falling_counter <= 64)

			falling_speed = (falling_counter) % 2;    //velocit� 0.5

		else if (falling_counter >= 64) 
		{
			out_counter++;

			if (out_counter >= 200)
			{
				in = false;
				//f = new Fire_Ball(pos(), dir, 1, 0, mario_up);
				out_counter = 0;
				falling_counter = 0;
			}
		}
		setY(y() + falling_speed);

	}

	//Game::instance()->changed_scene(level_change); ovviamente non se po fa 
	//animation_pipe = false;
	if (!in) 
	{

		if (jump_counter >= 0)
			jump_counter++;
		if (jump_counter <= 64)
			jumping_speed = jump_counter % 2;
		else if (jump_counter >= 64)
		{
			in_counter++;
			if (in_counter == 66)
				fire = new FireBallPiranha(pos().toPoint() + QPoint(0, 12), dir, angle); //todo mettere l'angle_id
			if (in_counter == 133)
				fire = new FireBallPiranha(pos().toPoint() + QPoint(0, 12), dir,angle);//todo mettere l'angle_id
			if (in_counter >= 200)
			{
				in = true;
				jump_counter = 0;
				in_counter = 0;
			}
		}
		setY(y() - jumping_speed);
	}
}



void PiranhaFire::animate()
{
	
	Entity::animate();

	if (animation_counter == 2)
	{
		std::cout << "marioptr: " << mario;
		mario = Game::instance()->getMario();
		std::cout << "marioptr2: " << mario;
	}

	//set the proper texture
	if(angle==30)
	{
		setPixmap(texture_crunch_up[(animation_counter / 20) % 2]);
	}
	else
		setPixmap(texture_crunch_down[(animation_counter / 20) % 2]);

	//mirror texture when dir is RIGHT
	if(dir==RIGHT)
		setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
}

void PiranhaFire::hit(Object* what, Direction fromDir)
{
	Object::hit(what, fromDir);

	if ((dynamic_cast<Inert*>(what) || dynamic_cast<Enemy*>(what))
		&& (fromDir == LEFT || fromDir == RIGHT))
		dir = inverse(dir);
}

void PiranhaFire::hurt()
{
	Sounds::instance()->play("stomp");//todo check the sound

	dying = true;
	moving = false;
}




