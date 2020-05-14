#pragma once

#include "Entity.h"

class Coin : public Entity
{
	protected:

		QPixmap texture_animation[4];

	public:
		
		Coin(QPoint position);

		virtual std::string name() { return "Coin"; }
		virtual void advance() {/*do nothing*/ }
		virtual void animate();
		virtual void hit(Object* what, Direction fromDir);
};