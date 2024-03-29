#include "SpinningItem.h"
#include "Sprites.h"
#include "EndLevelText.h"

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
	//raising from goalroulette
	if (animation_counter < 100)
		setY(y() - 2);

}

void SpinningItem::animate()
{
	if (animation_counter < 100)
		setPixmap(texture_animation[animation_counter++/5 %3]);
	else if (animation_counter >= 100 && animation_counter < 200)
		setPixmap(texture_animation[(animation_counter++/5 %2) + 3]);
	else if(animation_counter >=200)
		setPixmap(texture_animation[5]);
	
}