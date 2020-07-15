#include "Cheep.h"

#include "Sprites.h"
#include "Sounds.h"
#include <iostream>
#include "Game.h"

Cheep::Cheep(QPoint position, Direction direction) : Enemy()
{
	// set attribute
	pos_in = position;
	dir = direction;

	//flag 
	slow = true;
	falling = false;

	// durations
	death_duration = 250;

	// textures
	texture_swim[0] = Sprites::instance()->get("cheep-0");
	texture_swim[1] = Sprites::instance()->get("cheep-1");
	texture_death = Sprites::instance()->get("cheep-0").transformed(QTransform().scale(1, -1));


	// set texture and correct y-coordinate w.r.t. texture height
	setPixmap(texture_swim[0]);
	setPos(position);
	setZValue(2);
}

void Cheep::advance()
{
	//bounce and fall in the depth when dying
	if (dying)
	{
		if (death_counter >= 0 && death_counter <= 20)
			setY(y() - (animation_counter % 2));
		else
			setY(y() + 1);
		return;
	}

	prevPos = pos();
	
	//moving in the x-axis
	moving_speed = animation_counter % 2;
	setX(x() + (dir == RIGHT ? moving_speed : -moving_speed));

	//inverse direction when the virtual edges are reached
	if (x() >= pos_in.x() + 3 * 16 && dir == RIGHT)
		dir = inverse(dir);
	if (x() <= pos_in.x() - 3 * 16 && dir == LEFT)
		dir = inverse(dir);

	//floating during the time
	if (animation_counter % 64 == 0)
		setY(y() + 1);
	if (animation_counter % 64 == 4)
		setY(y() + 1);

	if (animation_counter % 64 == 8)
		setY(y() + 1);
	if (animation_counter % 64 == 12)
		setY(y() + 1);

	if (animation_counter % 64 == 16)
		setY(y() - 1);
	if (animation_counter % 64 == 20)
		setY(y() - 1);

	if (animation_counter % 64 == 24)
		setY(y() - 1);
	if (animation_counter % 64 == 28)
		setY(y() - 1);

	if (animation_counter % 64 == 32)
		setY(y() - 1);
	if (animation_counter % 64 == 36)
		setY(y() - 1);

	if (animation_counter % 64 == 40)
		setY(y() - 1);
	if (animation_counter % 64 == 44)
		setY(y() - 1);
	if (animation_counter % 64 == 48)
		setY(y() + 1);

	if (animation_counter % 64 == 52)
		setY(y() + 1);
	if (animation_counter % 64 == 56)
		setY(y() + 1);
	if (animation_counter % 64 == 60)
		setY(y() + 1);

	solveCollisions();
}

void Cheep::animate()
{
	Entity::animate();

	// set the proper texture
	if (dying)
	{
		setPixmap(texture_death);
	}
	else if (moving)
		setPixmap(texture_swim[(animation_counter / 8) % 2]);

	//mirror texture when dir==RIGHT
	if (dir == RIGHT)
		setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
}

void Cheep::hit(Object* what, Direction fromDir)
{
	Object::hit(what, fromDir);
}

void Cheep::hurt()
{
	Mario* mario = Game::instance()->getMario();
	mario->updateScore(100, pos().toPoint());
	Sounds::instance()->play("stomp");
	dying = true;
	moving = false;
}