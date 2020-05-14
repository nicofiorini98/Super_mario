#include "SecretBox.h"
#include "Sprites.h"
#include "Mario.h"
#include "Mushroom.h"
#include "Sounds.h"

SecretBox::SecretBox(QPoint position) : BouncingBlock()
{

	// textures
	texture_active    = Sprites::instance()->get("mega-secret-box");
	texture_inactive  = Sprites::instance()->get("mega-empty-box");

	// make background color (255, 178, 127) transparent
	texture_active.setMask(texture_active.createMaskFromColor(QColor(255, 178, 127)));
	texture_inactive.setMask(texture_inactive.createMaskFromColor(QColor(255, 178, 127)));

	setPixmap(texture_active);
	setPos(position);

	setZValue(3);
}

void SecretBox::animate()
{

	if (!active)
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
			hit_counter = -1;

		BouncingBlock::advance();
	}
}

void SecretBox::hit(Object *what, Direction fromDir)
{
	// do nothing if not active
	if(!active)
		return;

	Mario* mario = dynamic_cast<Mario*>(what);
	if(mario && fromDir == DOWN)
	{
		// start hit
		hit_counter = 0;

		moving = true;

		// disable box
		active = false;

		// play box hit sound
		Sounds::instance()->play("bump");
	}
}