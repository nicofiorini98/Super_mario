#include "Coin.h"
#include "Sprites.h"
#include "Mario.h"
#include "Sounds.h"
#include "SwitchBlock.h"
#include "Sounds.h"
#include "Hud.h"

Coin::Coin(QPoint position) : Entity()
{
	// flags
	falling = false;

	// textures
	texture_animation[0] = Sprites::instance()->get("coin-0");
	texture_animation[1] = Sprites::instance()->get("coin-1");
	texture_animation[2] = Sprites::instance()->get("coin-2");
	texture_animation[3] = Sprites::instance()->get("coin-3");

	// make background color (224, 163, 216) transparent
	for (int i = 0; i <= 3; i++)
		texture_animation[i].setMask(texture_animation[i].createMaskFromColor(QColor(224, 163, 216)));

	// set texture and position
	setPixmap(texture_animation[0]);
	setPos(position);
}

void Coin::animate()
{
	if (SwitchBlock::SwitchEffect())
		return;

	Entity::animate();
	
	setPixmap(texture_animation[(animation_counter/10)%4]);
}

void Coin::hit(Object* what, Direction fromDir)
{
	Mario* mario = dynamic_cast<Mario*>(what);
	if (mario)
	{
		Sounds::instance()->play("coin");
		Hud::instance()->updatePanel("CoinCounter");
		mario->update_score(50);
		die();
	}
}