#pragma once

#include "Collectable.h"

class LifeUp : public Collectable
{
	private:

		std::string lifes_number;
		QPixmap texture_extra_life;

	public:

		LifeUp(QPoint position, const std::string& _lifes_number);

		virtual std::string name() { return "LifeUp"; }
		virtual void hit(Object *what, Direction fromDir){/*do nothing*/ }
		virtual void animate(){/*do nothing*/ }
		virtual void advance();
};