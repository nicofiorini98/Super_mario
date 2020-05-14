#pragma once

#include "BouncingBlock.h"

class BrickBlock : public BouncingBlock
{
	protected:

		QPixmap texture_active[4];
		QPixmap texture_inactive[2];
		
	public:

		BrickBlock(QPoint position);

		virtual std::string name() { return "BrickBlock"; }
		virtual void advance();
		virtual void animate();
		virtual void hit(Object* what, Direction fromDir);
};