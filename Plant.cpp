#include "Plant.h"
#include "Mario.h"
#include "Sprites.h"

#include "Sounds.h"
#include <iostream>

Plant::Plant() : Enemy()
{
	mario = nullptr;
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
	texture_dying[0]  = Sprites::instance()->get("piranha-dying-0");
	texture_dying[1]  = Sprites::instance()->get("piranha-dying-1");
	texture_dying[2]  = Sprites::instance()->get("piranha-dying-0");
	texture_dying[3]  = Sprites::instance()->get("piranha-dying-1");
	texture_dying[4]  = Sprites::instance()->get("piranha-dying-2");
	texture_dying[5]  = Sprites::instance()->get("piranha-dying-3");
	texture_dying[6]  = Sprites::instance()->get("piranha-dying-2");
	texture_dying[7]  = Sprites::instance()->get("piranha-dying-3");
	texture_dying[8]  = Sprites::instance()->get("piranha-dying-4");
	texture_dying[9]  = Sprites::instance()->get("piranha-dying-5");
	texture_dying[10] = Sprites::instance()->get("piranha-dying-4");
	texture_dying[11] = Sprites::instance()->get("piranha-dying-5");
}


void Plant::advance() {


	//when mario goes out of sight of the piranha, then piranha is freezed
	if(mario)
	{
		if ((mario->pos().x() >= pos().x() + 16 * 16 || mario->pos().x() <= pos().x() - 16 * 16)
			|| (mario->pos().y() >= pos().y() + 10 * 16 || mario->pos().x() <= pos().x() - 12 * 16))
			freezed = true;
		else
			freezed = false;
	}
	
	
	if (freezed)
		return;
	//plant is out of pipe
	if (in) 
	{
		//descending phase in pipe
		if (falling_counter >= 0)
			falling_counter++;

		if (falling_counter <= 48)
			falling_speed = (falling_counter) % 2;

		else if (falling_counter >= 48)
		{
			falling_speed = 0;
			
		
			out_counter++;
			
			
			//plant is starting to raise out of pipe
			if (out_counter >= 200)
			{
				in = false;
				out_counter = 0;
				falling_counter = 0;
			}
			
		}
		setY(y() + falling_speed);
	}
	//plant is in pipe
	else
	{
		//raising phase out pipe
		if (jump_counter >= 0)
			jump_counter++;
		if (jump_counter <= 48)
			jumping_speed = jump_counter % 2;
		//plant is out pipe for a while
		else if (jump_counter >= 48)
		{
			in_counter++;
			//plant is starting to descend in pipe
			if (in_counter >= 200)
			{
				in = true;
				jump_counter = 0;
				in_counter = 0;
			}
		}
		setY(y() - jumping_speed);
	}
	solveCollisions();
}

void Plant::hit(Object* what, Direction fromDir)
{
	if (dynamic_cast<Mario*>(what) && dynamic_cast<Mario*>(what)->isRaccoonAttack())
		dying = true;
	Object::hit(what, fromDir);
}

void Plant::animate()
{
	if (dying)
		setPixmap(texture_dying[((animation_counter / 6) % 12)]);
}


QPainterPath Plant::shape() const
{
	QPainterPath path;

	path.addRect(2, boundingRect().top() + 3, boundingRect().width() - 4, boundingRect().bottom() - 6);

	return path;
}



