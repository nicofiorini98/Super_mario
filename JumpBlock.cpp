#include "JumpBlock.h"
#include "Sprites.h"

JumpBlock::JumpBlock(QPoint position)
{

	// textures
	texture_animation[0] = Sprites::instance()->get("jump-block-0");
	texture_animation[1] = Sprites::instance()->get("jump-block-1");
	texture_animation[2] = Sprites::instance()->get("jump-block-2");

	// make background color (224, 163, 216) transparent
	for (int i = 0; i < 3; i++)
		texture_animation[i].setMask(texture_animation[i].createMaskFromColor(QColor(224, 163, 216)));

	setPos(position);
}


void JumpBlock::animate()
{

}

void JumpBlock::advance()
{

}
