#include "JumpBlock.h"
#include "Sprites.h"
#include "Sounds.h"
#include "Mushroom.h"
#include "Flower.h"
#include <iostream>
#include "Leaf.h"

JumpBlock::JumpBlock(QPoint position)
{
	mario = nullptr;
	pos_in = position;

	hit_start_counter = -1;
	hit_duration = 0;
	animation_counter = 0;

	// textures
	texture_animation[0] = Sprites::instance()->get("jump-block-0");
	texture_animation[1] = Sprites::instance()->get("jump-block-1");
	texture_animation[2] = Sprites::instance()->get("jump-block-2");

	// make background color (224, 163, 216) transparent
	for (int i = 0; i < 3; i++)
		texture_animation[i].setMask(texture_animation[i].createMaskFromColor(QColor(224, 163, 216)));

	setPixmap(texture_animation[0]);
	setPos(position);
	setZValue(2);
}


void JumpBlock::animate()
{
	setPixmap(texture_animation[(animation_counter++/ 8) % 3]);
}

void JumpBlock::advance()
{
	
	if (hit_counter >= 0)
	{
		if (hit_counter == 0 && dir == DOWN)
			mario->bounceBlock();

		hit_start_counter++;
		// raising phase
		if (hit_counter < hit_duration / 2)
		{
			// here moving_speed is 1 by default
			hit_counter += moving_speed;

		}
		// falling phase
		else if (hit_counter >= hit_duration / 2 && hit_counter < hit_duration)
		{
			if (hit_counter == hit_duration / 2)
			{

				dir = inverse(dir);
			}
			if (dir == UP)
				moving_speed = 1;
			else
				moving_speed = hit_start_counter % 2 + 2;   // 2.5 speed
			hit_counter += moving_speed;
		}
		else
		{
			moving_speed = 1;
			
			hit_counter = -1;
			hit_start_counter = -1;
			moving = false;
			//different content depending by mario's mode
			if (active && !mario->isBig())
				new Mushroom(pos_in, UP, true);
			else if (active && mario->isBig())
				new Flower(pos_in,inverse(dir));
			active = false;
		}
		BouncingBlock::advance();

	}

}
void JumpBlock::hit(Object* what, Direction fromDir) {
	
	mario = dynamic_cast<Mario*>(what);
	if (mario && fromDir == DOWN && hit_counter == -1)
	{

		// start hit
		hit_counter = 0;
		hit_start_counter = 0;
		hit_duration = 20;

		// disable box
		dir = UP;

		moving = true;

		// play box hit sound
		Sounds::instance()->play("bump");
	}
	if (mario && fromDir == UP && hit_counter == -1)
	{
        //different content depending by mario's mode
		if (active && !mario->isBig())
			new Mushroom(pos_in, DOWN, true);
		else if (active && mario->isBig())
			new Flower(pos_in, DOWN);
		//hit by mario from UP and starting its rebounding phase
		mario->setRebound(false);
		active = false;
		dir = DOWN;
		hit_duration = 24;
		hit_counter = 0;
		hit_start_counter = 0;
		moving = true;

		// play box hit sound
		Sounds::instance()->play("bump");

	}
	
}