#include "Firework.h"
#include "Sprites.h"
#include <iostream>

Firework::Firework(QPoint position, const std::string& type) : Entity()
{
	collidable = false;
	moving = false;
	falling = false;

	//type = _type;
	if (type != "MUSHROOM" && type != "FLOWER" && type != "STAR")
		std::cerr << type << " is not a valid type\n";
	// textures
	//if (type == "MUSHROOM")
	//{
	//	texture_animation[0] = Sprites::instance()->get("mushroom-firework-1");
	//	texture_animation[1] = Sprites::instance()->get("mushroom-firework-2");
	//	texture_animation[2] = Sprites::instance()->get("mushroom-firework-3");
	//}
	//else if (type == "FLOWER")
	//{
	//	texture_animation[0] = Sprites::instance()->get("flower-firework-1");
	//	texture_animation[1] = Sprites::instance()->get("flower-firework-2");
	//	texture_animation[2] = Sprites::instance()->get("flower-firework-3");
	//}
	//else if(type == "STAR")
	//{
	//	texture_animation[0] = Sprites::instance()->get("star-firework-1");
	//	texture_animation[1] = Sprites::instance()->get("star-firework-2");
	//	texture_animation[2] = Sprites::instance()->get("star-firework-3");
	//}
	texture_animation[0] = Sprites::instance()->get(type + "-firework-1");
	texture_animation[1] = Sprites::instance()->get(type + "-firework-2");
	texture_animation[2] = Sprites::instance()->get(type + "-firework-3");
	
	setPos(position);
	setPixmap(texture_animation[0]);
}

void Firework::animate()
{

	setPixmap(texture_animation[animation_counter++ / 10 % 3]);
}