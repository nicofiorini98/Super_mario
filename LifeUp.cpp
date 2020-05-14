#include "LifeUp.h"
#include "Sprites.h"

LifeUp::LifeUp(QPoint position, const std::string& _lifes_number) : Collectable(position)
{
	lifes_number = _lifes_number;

	// texture
	texture_extra_life = Sprites::instance()->get(lifes_number + "-Up");

	setPos(position);
	setPixmap(texture_extra_life);
}

void LifeUp::advance()
{
}