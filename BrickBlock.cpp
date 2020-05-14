#include "BrickBlock.h"
#include "Sprites.h"


BrickBlock::BrickBlock(QPoint position) : BouncingBlock()
{
	
	animation_counter = 0;

	// textures
	texture_active[0]   = Sprites::instance()->get("brick-block-0");
	texture_active[1]   = Sprites::instance()->get("brick-block-1");
	texture_active[2]   = Sprites::instance()->get("brick-block-2");
	texture_active[3]   = Sprites::instance()->get("brick-block-3");
	texture_inactive[0] = Sprites::instance()->get("empty-block");
	texture_inactive[1] = Sprites::instance()->get("red-empty-block");
	

	setPixmap(texture_active[0]);
	setPos(position);
	setZValue(3);
}
 
void BrickBlock::advance()
{
	
	if (hit_counter >= 0)
	{
		// raising phase
		if (hit_counter < 10)
		{
			// here moving_speed is 1 by default
			hit_counter++;
		}
		// falling phase
		else if (hit_counter >= 10 && hit_counter < 14)
		{
			if (hit_counter == 10)
				dir = DOWN;	
			moving_speed = hit_counter % 2 + 2;   // 2.5 speed
			hit_counter++;
		}
		else
		{
			hit_counter = -1;
			moving = false;
		}
		BouncingBlock::advance();
	}	
}

void BrickBlock::animate()
{

	if (active)
		setPixmap(texture_active[(animation_counter++ / 20) % 4]);
	else
	{
		if (moving)
			setPixmap(texture_inactive[0]);
		else
			setPixmap(texture_inactive[1]);
	}
}

void BrickBlock::hit(Object* what, Direction fromDir)
{
	BouncingBlock::hit(what, fromDir);
}