#pragma once


#include "BouncingBlock.h"

class HiddenBlock : public BouncingBlock
{
	protected:

		QPixmap texture_hidden;
		QPixmap texture_inactive[2];

	public:

		HiddenBlock(QPoint position);

		virtual std::string name() { return "HiddenBlock"; }
		virtual void advance();
		virtual void animate();
		virtual void hit(Object* what, Direction fromDir);
};