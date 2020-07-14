#include "ScoreSpawnable.h"
#include "Sprites.h"
#include "Sounds.h"
#include "Game.h"

ScoreSpawnable::ScoreSpawnable(QPoint position,std::string id) : Entity()
{
	// set attributes
	collidable = false;

	texture = Sprites::instance()->get(id);
	

	// make background color (224, 163, 216) transparent
	texture.setMask(texture.createMaskFromColor(QColor(224, 163, 216)));

	// set texture and position
	setPixmap(texture);
	setPos(position - QPoint(0, pixmap().height()));

}


void ScoreSpawnable::animate()
{
	Entity::animate();
}

// @overridee
void ScoreSpawnable::advance()
{
	
	if (animation_counter < 50)
		setY(y()-1);
	else
	{
		Mario* mario = Game::instance()->getMario();
		die();
	}
}