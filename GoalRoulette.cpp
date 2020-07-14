#include "GoalRoulette.h"
#include "Sprites.h"
#include "Mario.h"
#include "SpinningItem.h"
#include "Game.h"

GoalRoulette::GoalRoulette(QPoint position) : Inert()
{
	walkable = false;
	active = true;

	animation_counter = 0;

	ranging_items = { std::make_pair("mushroom", Sprites::instance()->get("mushroom-item")),
			          std::make_pair("flower"  , Sprites::instance()->get("flower-item")),
			          std::make_pair("star"    , Sprites::instance()->get("star-item")),
	                  std::make_pair("empty"   , Sprites::instance()->get("no-item")) };

	setPos(position);
	setPixmap(ranging_items[0].second);
	content = ranging_items[0].first;
}

void GoalRoulette::animate()
{
	if (!active)
		return;

	setPixmap(ranging_items[(animation_counter++ / 6) % 3].second);
	content = ranging_items[(animation_counter / 6) % 3].first;
}

void GoalRoulette::hit(Object* what, Direction fromDir)
{
	
	if (dynamic_cast<Mario*>(what))
	{
		collidable = false;
		active = false;
		setPixmap(ranging_items[3].second);
		Game::instance()->setSpinningItem(new SpinningItem(QPoint(pos().x(), pos().y() - 16), content));
	}
}