#include "FireBallPiranha.h"
#include "Sprites.h"
#include <iostream>
#include "Iceberg.h"
#include "Game.h"

FireBallPiranha::FireBallPiranha(QPoint position, Direction direction, int _angle_dir) {

	//initialization default parameter
	moving = true;
	dir = direction;
	angle_dir = _angle_dir;
	// durations
	death_duration = 15;

	// textures
	texture[0] = Sprites::instance()->get("fire-ball-left-0");
	texture[1] = Sprites::instance()->get("fire-ball-left-1");
	texture[2] = Sprites::instance()->get("fire-ball-left-2");
	texture[3] = Sprites::instance()->get("fire-ball-left-3");

	setPixmap(texture[0]);
	setPos(position - QPoint(0, pixmap().height()));
	setZValue(2);
}

void FireBallPiranha::animate()
{
	Entity::animate();

	//set the proper texture
	if (dir == LEFT)
		setPixmap(texture[(animation_counter / 10) % 4]);
	else if (dir == RIGHT)
		setPixmap(texture[(animation_counter / 10) % 4].transformed(QTransform().scale(-1, 1)));
}


void FireBallPiranha::advance()
{
	//set the proper y-speed for manage the angle
	if (angle_dir == 30)
		setY(y()-animation_counter%2); 
	else if (angle_dir == -30)
		setY(y() + (animation_counter % 2));
	else if (angle_dir == -45)
		setY(y() + 1);

	//moving in the x direction
	if (dir == LEFT)
		setX(x() - 1);
	else
		setX(x() + 1);

	solveCollisions();
}

