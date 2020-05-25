#pragma once

#include "BouncingBlock.h"

class SecretBox : public BouncingBlock
{
	protected:

		// textures
		QPixmap texture_active[4];
		QPixmap texture_inactive;
		std::string type;

	public:

		SecretBox(QPoint position, spawnable_t _spawnable, std::string _type);

		// inherited methods
		virtual std::string name() {return "SecretBox";}
		virtual void animate();
		virtual void hit(Object *what, Direction fromDir);

		// @ovveride
		virtual void advance();
};