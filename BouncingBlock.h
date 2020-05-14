#pragma once

#include "Inert.h"
#include "Mario.h"

class BouncingBlock : public Inert
{
	protected:

		// attributes
		Direction dir;
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
	
		// pure virtual methods to be implemented
		virtual std::string name() = 0;
		virtual void animate() = 0;
		virtual void advance();
		virtual void hit(Object* what, Direction fromDir) = 0;
};