#include "BrickBlock.h"
#include "Sprites.h"
#include <iostream>
#include "Leaf.h"

BrickBlock::BrickBlock(QPoint position, std::string _type,spawnable_t _content) : BouncingBlock()
{
	if (_type != "ice" && _type != "")
		std::cerr << "Type not valid\n";
	type = _type;
	animation_counter = 0;
	content = _content;
	// textures
	if (_type == "") 
	{
		texture_active[0] = Sprites::instance()->get("brick-block-0");
		texture_active[1] = Sprites::instance()->get("brick-block-1");
		texture_active[2] = Sprites::instance()->get("brick-block-2");
		texture_active[3] = Sprites::instance()->get("brick-block-3");
	}
	else if (_type == "ice")
	{
		texture_active[0] = Sprites::instance()->get("ice-brick-block-0");
		texture_active[1] = Sprites::instance()->get("ice-brick-block-1");
		texture_active[2] = Sprites::instance()->get("ice-brick-block-2");
		texture_active[3] = Sprites::instance()->get("ice-brick-block-3");
	}
	texture_inactive[0] = Sprites::instance()->get("empty-block");
	texture_inactive[1] = Sprites::instance()->get("red-empty-block");

	setPixmap(texture_active[0]);
	setPos(position);
	setZValue(3);

}

void BrickBlock::advance()
{

	if (hit_counter >= 0)
	{
		// raising phase
		if (hit_counter < 10)
		{
			// here moving_speed is 1 by default
			hit_counter++;
		}
		// falling phase
		else if (hit_counter >= 10 && hit_counter < 14)
		{
			if (hit_counter == 10)
				dir = DOWN;
			moving_speed = hit_counter % 2 + 2;   // 2.5 speed
			hit_counter++;
		}
		else
		{
			hit_counter = -1;
			moving = false;
		}
		BouncingBlock::advance();
	}
}

void BrickBlock::animate()
{

	if (active)
		setPixmap(texture_active[(animation_counter++ / 20) % 4]);
	else
	{
		if (moving)
			setPixmap(texture_inactive[0]);
		else
			setPixmap(texture_inactive[1]);
	}
}

void BrickBlock::hit(Object* what, Direction fromDir)
{
	if(active)
	{
		if (content == LIFE && (fromDir == DOWN || fromDir == RIGHT))
		{
			new Mushroom(pos().toPoint(), UP, false);
			active = false;
		}

		if (content == LEAF && (fromDir == DOWN || fromDir == RIGHT))
		{
			new Leaf(pos().toPoint() + QPoint(4, 0));
			active = false;
		}
	}
	
	Mario* mario = dynamic_cast<Mario*>(what);
	if (type == "")
		BouncingBlock::hit(what, fromDir);

	
	else if (type == "ice" && (dynamic_cast<KoopaTroopa*>(what) && dynamic_cast<KoopaTroopa*>(what)->isShellMoving()||
            (dynamic_cast<Mario*>(what) && dynamic_cast<Mario*>(what)->isRaccoonAttack())))
	{
		collidable = false;
		setVisible(false);

		
		
		//the block is broken in four pieces
		new BrokenBlock(pos(), LEFT, true);
		new BrokenBlock(pos() + QPointF(0, 9), LEFT, false);
		new BrokenBlock(pos() + QPointF(8, 0), RIGHT, true);
		new BrokenBlock(pos() + QPointF(8, 9), RIGHT, false);
	}
}