#include "Plant.h"
#include "Mario.h"
#include "Sprites.h"

#include "Sounds.h"
Plant::Plant() : Enemy()
{

	in_counter = 0;
	out_counter = 0;
	in = true;
	falling_counter = 0;
	jump_counter = 0;

	slow = true;
	animation_div = 20;

	// durations
	death_duration = 64;

	//texture of plant dying
	texture_dying[0] = Sprites::instance()->get("piranha-dying-0");
	texture_dying[1] = Sprites::instance()->get("piranha-dying-1");
	texture_dying[2] = Sprites::instance()->get("piranha-dying-0");
	texture_dying[3] = Sprites::instance()->get("piranha-dying-1");
	texture_dying[4] = Sprites::instance()->get("piranha-dying-2");
	texture_dying[5] = Sprites::instance()->get("piranha-dying-3");
	texture_dying[6] = Sprites::instance()->get("piranha-dying-2");
	texture_dying[7] = Sprites::instance()->get("piranha-dying-3");
	texture_dying[8] = Sprites::instance()->get("piranha-dying-4");
	texture_dying[9] = Sprites::instance()->get("piranha-dying-5");
	texture_dying[10] = Sprites::instance()->get("piranha-dying-4");
	texture_dying[11] = Sprites::instance()->get("piranha-dying-5");
}


void Plant::advance() {

	if (freezed)
		return;

	if (in) 
	{
		if (falling_counter >= 0)
			falling_counter++;

		if (falling_counter <= 48)
			falling_speed = (falling_counter) % 2;    //0.5 speed

		else if (falling_counter >= 48)
		{
			out_counter++;
			if (out_counter >= 200)
			{
				in = false;
				out_counter = 0;
				falling_counter = 0;
			}
		}
		setY(y() + falling_speed);
	}
	else
	{
		if (jump_counter >= 0)
			jump_counter++;
		if (jump_counter <= 48)
			jumping_speed = jump_counter % 2;
		else if (jump_counter >= 48)
		{
			in_counter++;
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

void Plant::hit(Object* what, Direction fromDir)
{
	Object::hit(what, fromDir);
}

void Plant::animate()
{
	if (dying)
		setPixmap(texture_dying[((animation_counter / 6) % 12)]);
}

