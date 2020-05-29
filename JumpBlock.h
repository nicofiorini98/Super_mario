#pragma once

#include "BouncingBlock.h"

class JumpBlock : public BouncingBlock
{
	protected:

		QPixmap texture_animation[3];

	public:

		JumpBlock(QPoint position,spawnable_t _content);

		virtual std::string name() { return "JumpBlock"; }
		virtual void hit(Object* what, Direction fromDir);
		virtual void animate();
		virtual void advance();

};