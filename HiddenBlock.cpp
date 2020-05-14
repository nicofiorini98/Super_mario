#include "HiddenBlock.h"
#include "Sprites.h"
#include "Sounds.h"
#include "CoinSpawnable.h"

HiddenBlock::HiddenBlock(QPoint position) : BouncingBlock()
{
	// textures
	texture_hidden      = Sprites::instance()->get("transparent-block");
	texture_inactive[0] = Sprites::instance()->get("empty-block");
	texture_inactive[1] = Sprites::instance()->get("red-empty-block");

	setPixmap(texture_hidden);
	setPos(position);
}

void HiddenBlock::advance()
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

void HiddenBlock::animate()
{
	if (!active)
	{
		if (moving)
			setPixmap(texture_inactive[0]);
		else
			setPixmap(texture_inactive[1]);
	}
}

void HiddenBlock::hit(Object* what, Direction fromDir)
{
	if (!active)
		return;

	Mario* mario = dynamic_cast<Mario*>(what);
	if (mario && fromDir == DOWN)
	{
		// start hit
		hit_counter = 0;
		
		moving = true;

		new CoinSpawnable(QPoint(x(), y()));

		active = false;

		// play box hit sound
		Sounds::instance()->play("bump");
	}
}