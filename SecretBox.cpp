#include "SecretBox.h"
#include "Sprites.h"
#include "Mario.h"
#include "Sounds.h"
#include <iostream>
#include "Game.h"

SecretBox::SecretBox(QPoint position,spawnable_t _spawnable) : BouncingBlock()
{
	//todo vedere se c'è un animazione nella mega secret box
	// textures
	animation_counter = 0;
	spawn_counter = -1;
	content = _spawnable;

	texture_active[0] = Sprites::instance()->get("mega-secret-box");
	texture_inactive = Sprites::instance()->get("mega-empty-box");
	
	
	// make background color (255, 178, 127) transparent
	texture_active[0].setMask(texture_active[0].createMaskFromColor(QColor(255, 178, 127)));
	texture_inactive.setMask(texture_inactive.createMaskFromColor(QColor(255, 178, 127)));

	setPixmap(texture_active[0]);
	setPos(position);

	setZValue(3);
}

void SecretBox::animate()
{
	if (active)
		setPixmap(texture_active[0]);
	else
		setPixmap(texture_inactive);
}
	
	

// @override
void SecretBox::advance()
{
	if(hit_counter >= 0)
	{
		// raising phase
		if (hit_counter < 12)
			hit_counter++;
		
		// falling phase
		else if(hit_counter >= 12 && hit_counter < 24)
		{
			if (hit_counter == 12)
				dir = DOWN;
			hit_counter++;
		}
		else
		{
			hit_counter = -1;
			spawn_counter = 0;
			//new Mushroom(QPoint(x(), y()), UP);
			BouncingBlock::spawn(UP);  //spawn of mushroom
		}
		BouncingBlock::advance();
	}
	if (spawn_counter >= 0) {
		spawn_counter++;
		if (spawn_counter == 120)
			BouncingBlock::spawn(UP);  //spawn of mushroom
		else if (spawn_counter == 240) {
			BouncingBlock::spawn(UP);  //spawn of mushroom
			spawn_counter = -1;

		}
	}
}

void SecretBox::hit(Object* what, Direction fromDir)
{
	BouncingBlock::hit(what, fromDir);
}

//void SecretBox::hit(Object *what, Direction fromDir)
//{
//	
//	// do nothing if not active
//	if(!active)
//		return;
//
//	mario = dynamic_cast<Mario*>(what);
//	if(mario && fromDir == DOWN)
//	{
//		// start hit
//		hit_counter = 0;
//
//		moving = true;
//
//		hit_from = fromDir;
//
//		// disable box
//		active = false;
//		
//		//BouncingBlock::spawn();
//
//		// play box hit sound
//		Sounds::instance()->play("bump");
//	}
//}
