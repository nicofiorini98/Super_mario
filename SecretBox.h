#pragma once

#include "BouncingBlock.h"

class SecretBox : public BouncingBlock
{
	protected:

		// textures
		QPixmap texture_active[4];
		QPixmap texture_inactive;
		Direction hit_from;

	public:

		SecretBox(QPoint position, spawnable_t _spawnable);
		// inherited methods
		//virtual void spawn(Direction _dir){}
		virtual std::string name() {return "SecretBox";}
		virtual void animate();
		virtual void hit(Object *what, Direction fromDir);

		// @override
		virtual void advance();
};