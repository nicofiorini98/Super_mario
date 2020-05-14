#pragma once

#include "Inert.h"

class EndLevelText : public Inert
{
	private:

		QPixmap texture_text ;

	public:

		EndLevelText(QPoint position, const std::string& text);

		virtual std::string name() { return "EndLevelText"; }
		virtual void hit(Object *what, Direction fromDir) { /*do nothing*/ }
};