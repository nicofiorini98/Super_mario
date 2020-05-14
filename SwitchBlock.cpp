#include "SwitchBlock.h"
#include "Sprites.h"
#include "Mario.h"
#include "Sounds.h"
#include "Game.h"

#include <QTimer>

bool SwitchBlock::switch_effect = false;

SwitchBlock::SwitchBlock(QPoint position) :  Inert()
{
	
	// flags
	spawning = true;
	active = false;
	collidable = false;
	walkable = false;
	

	animation_counter = 0;

	// textures
	texture_spawning[0]  = Sprites::instance()->get("switch-block-0");
	texture_spawning[1]  = Sprites::instance()->get("switch-block-1");
	texture_spawning[2]  = Sprites::instance()->get("switch-block-2");
	texture_spawning[3]  = Sprites::instance()->get("switch-block-3");
	texture_spawning[4]  = Sprites::instance()->get("switch-block-4");
	texture_spawning[5]  = Sprites::instance()->get("switch-block-5");
	texture_spawning[6]  = Sprites::instance()->get("switch-block-6");
	texture_spawning[7]  = Sprites::instance()->get("switch-block-7");
	texture_spawning[8]  = Sprites::instance()->get("switch-block-8");
	texture_spawning[9]  = Sprites::instance()->get("switch-block-9");
	texture_spawning[10] = Sprites::instance()->get("switch-block-10");
	texture_active[0]    = Sprites::instance()->get("switch-block-11");
	texture_active[1]    = Sprites::instance()->get("switch-block-12");
	texture_active[2]    = Sprites::instance()->get("switch-block-13");
	texture_smashed      = Sprites::instance()->get("switch-block-smashed");

	// make background color (224, 163, 216) transparent
	for (int i = 0; i < 3; i++)
		texture_active[i].setMask(texture_active[i].createMaskFromColor(QColor(224, 163, 216)));
	texture_smashed.setMask(texture_smashed.createMaskFromColor(QColor(224, 163, 216)));
	
	setPixmap(texture_spawning[0]);
	setPos(position);
}

void SwitchBlock::animate()
{	
	if (spawning)
	{
		setPixmap(texture_spawning[animation_counter++ % 11]);
		if (animation_counter == 47)
		{
			spawning = false;
			active = true;
			collidable = true;
		}
	}
	else if (active)
		setPixmap(texture_active[(animation_counter++ /50) % 3]);
    else
		setPixmap(texture_smashed);
}

void SwitchBlock::hit(Object* what, Direction fromDir)
{
	Mario* mario = dynamic_cast<Mario*>(what);
	if (mario && fromDir == UP)
	{
		active = false;
		collidable = false;
		switch_effect = true;

		// stop game's current music and play "switch-hit" sound
		Game::instance()->stopMusic();
		Sounds::instance()->play("switch-hit");

		// play "pickabox" sound when "switch-hit" sound it's over
		QTimer::singleShot(700, Game::instance(), []() { Sounds::instance()->play("pickabox"); });

		// scheduling switch-effect's end (8500 ms after "switch-hit" sound started) 
		QTimer::singleShot(8500, Game::instance(), [this]() { switch_effect = false; Game::instance()->playMusic(); });
	}
}