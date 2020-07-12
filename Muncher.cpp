#include "Muncher.h"
#include "Sprites.h"
#include "Game.h"
#include "SwitchBlock.h"

Muncher::Muncher(QPoint position) : Enemy()
{
	// flags
	moving = false;

	// textures
	texture_animation[0] = Sprites::instance()->get("muncher-0");
	texture_animation[1] = Sprites::instance()->get("muncher-1");
	texture_animation[2] = Sprites::instance()->get("muncher-2");

	// make background color (224, 163, 216) transparent
	for (int i = 0; i < 3; i++)
		texture_animation[i].setMask(texture_animation[i].createMaskFromColor(QColor(224, 163, 216)));

	temp_coin = nullptr;

	setPixmap(texture_animation[0]);
	setPos(position);
}

void Muncher::animate()
{
	if (SwitchBlock::SwitchEffect())
	{
		if (!temp_coin)
		{
			collidable = false;
			hide();
			temp_coin = new Coin(QPoint(pos().toPoint()));
		}
		if (temp_coin->isDead())
			die();
	}
	else
	{
		// aggiungere commenti qua
		if (!isVisible())
		{
			collidable = true;
			setVisible(true);
			temp_coin->die();
		}
		setPixmap(texture_animation[(animation_counter++ / 8) % 3]);
	}
}

void Muncher::die()
{
	if (!dead)
		dead = true;
}