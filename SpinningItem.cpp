#include "SpinningItem.h"
#include "Sprites.h"
#include "EndLevelText.h"
#include "Firework.h"

SpinningItem::SpinningItem(QPoint position, const std::string& _id) : Collectable (position)
{
	// for debug
	collidable = true;

	id = _id;

	// textures
	texture_animation[0] = Sprites::instance()->get("spinning-"+id+"-1");
	texture_animation[1] = Sprites::instance()->get("spinning-"+id+"-2");
	texture_animation[2] = Sprites::instance()->get("spinning-item-3");
	texture_animation[3] = Sprites::instance()->get("spinning-item-4");
	texture_animation[4] = Sprites::instance()->get("spinning-item-5");
	texture_animation[5] = Sprites::instance()->get("spinning-item-6");

	setPos(position);
}

void SpinningItem::advance()
{
	if (animation_counter < 100)
		setY(y() - 2);
	//else if (animation_counter == 100 && mario->isFreezed() )
	//	new Firework(QPoint(pos().toPoint()), id);
}

void SpinningItem::animate()
{
	if (animation_counter < 100)
		setPixmap(texture_animation[animation_counter++/5 %3]);
	else if (animation_counter >= 100 && animation_counter < 200)
		setPixmap(texture_animation[(animation_counter++/5 %2) + 3]);
	else if(animation_counter >=200)
		setPixmap(texture_animation[5]);
	// sposta nell advance la seguente riga opportunamente
		//setPos(pos() - QPointF(0,16));
}