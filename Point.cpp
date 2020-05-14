#include "Point.h"
#include "Sprites.h"
#include <iostream>

Points::Points(QPoint position, const std::string& points_number) : Entity()
{
	if (points_number != "100")
		std::cerr << "points number not allowed\n";

	dir = UP;

	texture_number = Sprites::instance()->get(points_number);

	setPixmap(texture_number);
	setPos(position);
}

void Points::advance()
{
	
	//if ()
	//	moving_speed = animation_counter++%2 +1 ;
}