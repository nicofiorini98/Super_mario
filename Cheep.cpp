#include "Cheep.h"

#include "Sprites.h"
#include "Sounds.h"
#include <iostream>

Cheep::Cheep(QPoint position, Direction direction) : Enemy()
{
	// set attribute
	pos_in = position;
	dir = direction;
	slow = true;
	falling = false;
	moving_start_counter = 0;
	// animation divisor
	animation_div = 8;

	// durations
	death_duration = 250;

	// textures
	texture_swim[0] = Sprites::instance()->get("cheep-0");
	texture_swim[1] = Sprites::instance()->get("cheep-1");
	texture_death = Sprites::instance()->get("cheep-0").transformed(QTransform().scale(1, -1));


	// set texture and correct y-coordinate w.r.t. texture height
	setPixmap(texture_swim[0]);
	setPos(position - QPoint(0, pixmap().height()));
	setZValue(2);
}

void Cheep::advance()
{
	//advance when dying
	if(dying)
	{
		if (death_counter >= 0 && death_counter <= 20)
			setY(y() - (animation_counter % 2));
		else
			setY(y() + 1);
		return;
	}
	
	//moving in the x-axis
	moving_speed = animation_counter % 2;
	setX(x() + (dir == RIGHT ? moving_speed : -moving_speed));

	//inverse direction when the virtual edges are reached
	if (x() >= pos_in.x() + 3 * 16 && dir == RIGHT)
		dir = inverse(dir);
	if (x() <= pos_in.x() - 3 * 16 && dir == LEFT)
		dir = inverse(dir);

	//moving in the y-axis
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
		std::cout << "morete\n";
		setPixmap(texture_death);
	}
	else if (moving)
		setPixmap(texture_swim[(animation_counter / animation_div) % 2]);

	//mirror texture when dir==RIGHT
	if (dir == RIGHT)
		setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
}

void Cheep::hit(Object* what, Direction fromDir)
{
	Object::hit(what, fromDir);

	//if ((dynamic_cast<Inert*>(what) || dynamic_cast<Enemy*>(what))
	//	&& (fromDir == LEFT || fromDir == RIGHT))
	//	dir = inverse(dir);
}

void Cheep::hurt()
{
	Sounds::instance()->play("stomp");
	dying = true;
	moving = false;
}