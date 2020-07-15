#pragma once

#include "Inert.h"
#include "Mario.h"
#include "Mushroom.h"
//#include "Flower.h"/#include "Collectable.h"

class BouncingBlock : public Inert
{
	protected:

		// attributes
		Direction dir;
		spawnable_t content;
	
		bool active;
		bool moving;
		Mario* mario;

		int moving_speed;
		
		// counters
		int hit_counter;
		int animation_counter;


	public:

		BouncingBlock();

		bool isActive() { return active; }
		virtual void spawn(Direction _dir);
	
		// pure virtual methods to be implemented
		virtual std::string name() = 0;
		virtual void animate() = 0;
		virtual void advance();
		virtual void hit(Object* what, Direction fromDir) = 0;
};