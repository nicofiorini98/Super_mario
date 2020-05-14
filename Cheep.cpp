#include "Cheep.h"

#include "Sprites.h"
#include "Sounds.h"


Cheep::Cheep(QPoint position, Direction direction) : Enemy()
{
	
	pos_in = position;
	dir = direction;
	slow = true;
	falling = false;

	// animation divisor
	animation_div = 8;

	// durations
	death_duration = 100;

	// textures
	texture_swim[0] = Sprites::instance()->get("cheep-0");
	texture_swim[1] = Sprites::instance()->get("cheep-1");
	texture_death   = Sprites::instance()->get("cheep-0").transformed(QTransform().scale(-1, 1));
	
	// set texture and correct y-coordinate w.r.t. texture height
	setPixmap(texture_swim[0]);
	setPos(position - QPoint(0, pixmap().height()));

	setZValue(2);
}

void Cheep::advance()
{
	int delta = dir == RIGHT ? 16 : -16;
	setX(x() + delta);
	if (x()==pos_in.x() + 3*16 || x() == pos_in.x() - 3*16)
		dir = inverse(dir);
	setX(x() - delta);

	Entity::advance();
}

void Cheep::animate()
{
	Entity::animate();

	// save current texture height (for later correction)
	int prev_h = boundingRect().height();

	// set the proper texture
	if (dying)
		setPixmap(texture_death);
	else if (moving)
		setPixmap(texture_swim[(animation_counter / animation_div) % 2]);

	//era dello goomba perchè da morto cambiava altezza
	//// correct y position if texture height changed
	int cur_h = boundingRect().height();
	if (prev_h != cur_h)
	setY(y() - (cur_h - prev_h));

	if (dir == RIGHT)
		setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
}

void Cheep::hit(Object* what, Direction fromDir)
{
	
	Object::hit(what, fromDir);

	if ((dynamic_cast<Inert*>(what) || dynamic_cast<Enemy*>(what))
		&& (fromDir == LEFT || fromDir == RIGHT))
		dir = inverse(dir);
}

void Cheep::hurt()
{
	Sounds::instance()->play("stomp");
	dying = true;
	moving = false;
}