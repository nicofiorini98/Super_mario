#include "Mushroom.h"
#include "Mario.h"
#include "Sounds.h"
#include "Sprites.h"


Mushroom::Mushroom(QPoint position, bool _red) : Collectable(position)
{
	// set attributes
	red = _red;

	// set texture and position
	setPixmap(Sprites::instance()->get(red ? "mushroom-red" : "mushroom-green"));
	setPos(position);

	// play mushroom sound
	Sounds::instance()->play("spawn");
}

void Mushroom::animate()
{
	Entity::animate();

	// if mushroom fully emerges from spawn position, 
	// start moving right and become collidable
	if(y() == spawned_position.y()-pixmap().height())
	{
		collidable = true;
		falling = true;
		slow = true;
		moving_speed_div = 2;
		dir = RIGHT;
	}
}

void Mushroom::hit(Object *what, Direction fromDir)
{
	
	Object::hit(what, fromDir);

	// if hit by Mario, Mario eats mushroom and mushroom dies
	Mario* mario = dynamic_cast<Mario*>(what);
	if(mario)
	{
		mario->powerUp(MUSHROOM);
		die();
		return;
	}

	// if hit from its left or right side, it
	// has to move to the opposite direction w.r.t. the one
	// is he currently moving
	if(fromDir == RIGHT || fromDir == LEFT)
		setDirection(inverse(dir));
}