#pragma once

#include "Entity.h"
#include <map>

class Points : public Entity
{
	private:

		QPixmap texture_number;
		//std::map<std::string, QPixmap> points;

	public:

		Points(QPoint position, const std::string& score);

		virtual std::string name() { return "Points"; }
		virtual void advance();
		virtual void animate(){/*do nothing*/}
		virtual void hit(Object *what, Direction fromDir){/*do nothing*/}
};