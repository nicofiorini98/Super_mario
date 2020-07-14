#include "SecretBox.h"
#include "Sprites.h"
#include "Mario.h"
#include "Sounds.h"
#include <iostream>
#include "Game.h"

SecretBox::SecretBox(QPoint position,spawnable_t _spawnable) : BouncingBlock()
{
	
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

