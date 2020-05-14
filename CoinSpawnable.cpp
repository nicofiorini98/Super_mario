#include "CoinSpawnable.h"
#include "Sprites.h"
#include "Sounds.h"

CoinSpawnable::CoinSpawnable(QPoint position) : Entity()
{
	// set attributes
	collidable = false;

	// create textures
	texture_animation[0] = Sprites::instance()->get("coin-spawnable-0");
	texture_animation[1] = Sprites::instance()->get("coin-spawnable-1");
	texture_animation[2] = Sprites::instance()->get("coin-spawnable-2");
	texture_animation[3] = texture_animation[1];

	// make background color (224, 163, 216) transparent
	for(int i=0; i<4; i++)
		texture_animation[i].setMask(texture_animation[i].createMaskFromColor(QColor(224, 163, 216)));

	// set texture and position
	setPixmap(texture_animation[0]);
	setPos(position-QPoint(0, pixmap().height()));

	// play coin sound
	Sounds::instance()->play("coin");
}


void CoinSpawnable::animate()
{
	Entity::animate();

	setPixmap(texture_animation[(animation_counter/10)%4]);
}

// @override
void CoinSpawnable::advance()
{
	if(animation_counter < 28)
		setY(y()-2);
	else if(animation_counter >= 28 && animation_counter < 54)
		setY(y()+2);
	else
		die();
}