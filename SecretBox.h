#pragma once

#include "BouncingBlock.h"

class SecretBox : public BouncingBlock
{
	protected:

		// textures
		QPixmap texture_active;
		QPixmap texture_inactive;

	public:

		SecretBox(QPoint position);

		// inherited methods
		virtual std::string name() {return "SecretBox";}
		virtual void animate();
		virtual void hit(Object *what, Direction fromDir);

		// @ovveride
		virtual void advance();
};