#include "Splash.h"

Splash::Splash(QPointF _pos)
{
	falling = false;
	moving = false;
	collidable = false;
	animation_div = 5;
	
	pos = _pos;
	
	texture_splash[0] = Sprites::instance()->get("Splash-0");
	texture_splash[1] = Sprites::instance()->get("Splash-1");
	texture_splash[2] = Sprites::instance()->get("Splash-2");
	texture_splash[3] = Sprites::instance()->get("Splash-3");
	texture_splash[4] = Sprites::instance()->get("Splash-4");
	
	setPixmap(texture_splash[0]);
	
	setPos(pos.x(),15*16+2);
	setZValue(3);
}

void Splash::animate()
{
	Entity::animate();
		
		setPixmap(texture_splash[(animation_counter / animation_div) % 5]);
	//ending of splash animation and disappear
	if (animation_counter == 5 * animation_div ) {
		animation_counter = -1;
		setVisible(false);
	}
}