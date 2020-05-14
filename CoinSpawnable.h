#pragma once

#include "Entity.h"

class CoinSpawnable : public Entity
{
	protected:

		// textures
		QPixmap texture_animation[4];

	public:

		CoinSpawnable(QPoint position);

		// inherited methods
		virtual std::string name() {return "CoinSpawnable";}
		virtual void animate();
		virtual void hit(Object *what, Direction fromDir){}

		// @override
		virtual void advance();
};