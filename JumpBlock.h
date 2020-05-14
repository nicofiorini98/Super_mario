#pragma once

#include "BouncingBlock.h"

class JumpBlock : public BouncingBlock
{
	protected:

		QPixmap texture_animation[3];

	public:

		JumpBlock(QPoint position);

		virtual std::string name() { return "JumpBlock"; }
		virtual void animate();
		virtual void advance();

};