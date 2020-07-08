#include "Piranha.h"
#include "Mario.h"
#include "Sprites.h"

#include "Sounds.h"
Piranha::Piranha(QPoint position, Direction direction, bool _red, bool _rotate) :Plant()
{
	
	in_counter = 0;
	out_counter = 0;
	in = true;
	falling_counter = 0;
	jump_counter = 0;

	// set attribute
	rotate = _rotate;
	red = _red;
	pos_in = position;
	dir = direction;
	slow = true;  

	// textures
	if (!red && !rotate)
	{
		texture_crunch[0] = Sprites::instance()->get("green-plant-0");
		texture_crunch[1] = Sprites::instance()->get("green-plant-1");
	}
	else if (red && !rotate)
	{
		texture_crunch[0] = Sprites::instance()->get("red-plant-0");
		texture_crunch[1] = Sprites::instance()->get("red-plant-1");
	}
	else if (!red && rotate)
	{
		texture_crunch[0] = Sprites::instance()->get("green-plant-0").transformed(QTransform().scale(1, -1));
		texture_crunch[1] = Sprites::instance()->get("green-plant-1").transformed(QTransform().scale(1, -1));
	}
	else if (red && rotate)
	{
		texture_crunch[0] = Sprites::instance()->get("red-plant-0").transformed(QTransform().scale(1, -1));
		texture_crunch[1] = Sprites::instance()->get("red-plant-1").transformed(QTransform().scale(1, -1));
	}

	// set texture and correct y-coordinate w.r.t. texture height

	setPixmap(texture_crunch[0]);

	setPos(position - QPoint(0, pixmap().height()));
	setZValue(2);
}


void Piranha::advance() {

	if (dying)
		return;
	
	Plant::advance();
	
}

void Piranha::animate()
{
	Entity::animate();

	// save current texture height (for later correction)
	int prev_h = boundingRect().height();


	setPixmap(texture_crunch[(animation_counter / animation_div) % 2]);

	//// correct y position if texture height changed
	//todo vedere se serve per la morte, credo si può togliere
	int cur_h = boundingRect().height();
	if (prev_h != cur_h)
		setY(y() - (cur_h - prev_h));

}
void Piranha::hit(Object* what, Direction fromDir)
{
	Object::hit(what, fromDir);

}

void Piranha::hurt()
{
	Sounds::instance()->play("stomp");

	dying = true;
	moving = false;
}

