#include "JumpBlock.h"
#include "Sprites.h"
#include "Sounds.h"

JumpBlock::JumpBlock(QPoint position,spawnable_t _content)
{
	// textures
	texture_animation[0] = Sprites::instance()->get("jump-block-0");
	texture_animation[1] = Sprites::instance()->get("jump-block-1");
	texture_animation[2] = Sprites::instance()->get("jump-block-2");

	//content of the block
	content = _content;
	
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


void JumpBlock::hit(Object* what, Direction fromDir)
{
	// do nothing if not active
	if (!active)
		return;

	Mario* mario = dynamic_cast<Mario*>(what);
	if (mario && fromDir == DOWN)
	{
		// start hit
		hit_counter = 0;

		moving = true;

		// disable box
		active = false;

		//BouncingBlock::spawn();

		// play box hit sound
		Sounds::instance()->play("bump");
	}
}