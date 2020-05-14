#pragma once
#include "Entity.h"

class Enemy : public Entity
{
	protected:

		// animation divisors
		int animation_div;

	public:

		Enemy();

		// pure virtual methods that must be implemented
		virtual std::string name() = 0;
		virtual void animate() = 0;
		virtual void hit(Object *what, Direction fromDir) = 0;

		// enemies can be hurt
		virtual void hurt() = 0;
};