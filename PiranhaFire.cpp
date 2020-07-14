#include "PiranhaFire.h"
#include "Mario.h"
#include "Sprites.h"

#include "Sounds.h"
#include "Game.h"
#include <iostream>

PiranhaFire::PiranhaFire(QPoint position, Direction direction) : Plant()
{
	in_counter = 0;
	out_counter = 0;
	in = true;
	falling_counter = 0;
	jump_counter = 0;
	angle = 30;
	pos_in = position;
	dir = direction;
	
	// textures
	texture_crunch_up[0]   = Sprites::instance()->get("plant-fire-up-0");
	texture_crunch_up[1]   = Sprites::instance()->get("plant-fire-up-1");
	texture_crunch_down[0] = Sprites::instance()->get("plant-fire-down-0");
	texture_crunch_down[1] = Sprites::instance()->get("plant-fire-down-1");


	setPixmap(texture_crunch_up[0]);

	setPos(position - QPoint(0, pixmap().height()));
	setZValue(2);
}


void PiranhaFire::advance()
{

	if(dying)
		return;

	Plant::advance();

	if(mario !=nullptr)
	{
		//depending from mario's position, plant shoots fireballs with different angles and directions
		if (mario->pos().y() <= pos().y() - 10)
			angle = 30;
		else if (mario->pos().y() <= pos().y() + 10)
			angle = -30;
		else
			angle = -45;


		if (mario->pos().x() >= pos().x() + boundingRect().width() / 2)
			dir = RIGHT;
		else
			dir = LEFT;
	}
	//shooting fireballs at regular intervals
	if (in_counter == 66)
		fire = new FireBallPiranha(pos().toPoint() + QPoint(0, 12), dir, angle);
	if (in_counter == 133)
		fire = new FireBallPiranha(pos().toPoint() + QPoint(0, 12), dir, angle);
}


void PiranhaFire::animate()
{
	
	Entity::animate();
	if(dying)
	{
		Plant::animate();
		return;
	}
	//after 1 frame plants get mario's address,
    //otherwise mario points to null at starting of the game, and crash
	if (animation_counter == 1)
		mario = Game::instance()->getMario();
	

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

}

void PiranhaFire::hurt()
{
	Sounds::instance()->play("stomp");
	//update score of mario and begins to die
	mario->updateScore(100, pos().toPoint());
	dying = true;
	moving = false;
}




