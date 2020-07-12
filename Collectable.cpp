#include "Collectable.h"

Collectable::Collectable(QPoint position) 
{
	// set attributes
	spawned_position = position;

	// set flags (spawn phase)
	collidable = false;
	moving = true;
	dir = UP;				
	falling = false;
	moving_speed = 1;	
	moving_speed_div = 6;
	slow = true;
	falling_speed = 1;
	death_duration = 0;

	setZValue(2); 
}