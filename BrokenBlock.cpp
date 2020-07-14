#include "BrokenBlock.h"
#include "Sprites.h"

BrokenBlock::BrokenBlock(QPointF _pos, Direction _dir, bool _big_jump) : Entity()
{

	setPos(_pos);
	dir = _dir;
	setZValue(3);
	big_jump = _big_jump;
	falling = false;
	moving_speed_div = 3;
	duration = 28;
	
	texture_broken[0] = Sprites::instance()->get("broken-block");
	texture_broken[0].setMask(texture_broken[0].createMaskFromColor(QColor(224, 163, 216)));
	texture_broken[1] = texture_broken[0].transformed(QTransform().scale(-1, 1));
	setPixmap(texture_broken[0]);
	collidable = false;
}

void BrokenBlock::animate()
{
	Entity::animate();
	setPixmap(texture_broken[(animation_counter / 20) % 2]);
}

void BrokenBlock::advance()
{

	//each brokenblock describes jump trajectory,
    //two of these brokenblock do a small jump, others a big jump
	if (dir == RIGHT)
		setX(x() + animation_counter % 2);
	else
		setX(x() - animation_counter % 2);


	
	if (animation_counter <= duration) {

		setY(y() - moving_speed);


		if (animation_counter < duration / 4) 
		{
			if (!big_jump)
				moving_speed = 3;
			else
				moving_speed = 9;
		}
		if (animation_counter > duration / 4 && animation_counter < 2 * duration / 4) 
		{
			if (!big_jump)
				moving_speed = 2;
			else
				moving_speed = 6;
		}
		if (animation_counter > 2 * duration / 4 && animation_counter < 3 * duration / 4) 
		{
			if (!big_jump)
				moving_speed = 1;
			else
				moving_speed = 3;
		}
		if (animation_counter > 3 * duration / 4 && animation_counter < 4 * duration / 4) 
		{
			if (!big_jump)
				moving_speed_div = 2;
			else
				moving_speed_div = 4;
			moving_speed = animation_counter % moving_speed_div == 0;
		}
	}
	else if (animation_counter > duration) 
	{
		setY(y() + moving_speed);
		if (animation_counter < duration + duration / 5) 
		{
			moving_speed_div = 2;
			moving_speed = animation_counter % moving_speed_div == 0;
		}
		if (animation_counter > duration + duration / 4 && animation_counter < duration + 2 * duration / 4) 
		{
			moving_speed = 1;
		}
		if (animation_counter > duration + 2 * duration / 4 && animation_counter < duration + 3 * duration / 4) 
		{
			moving_speed = 2;
		}
		if (animation_counter > duration + 3 * duration / 4 && animation_counter < duration + 4 * duration / 4) 
		{
			moving_speed = 3;
		}
	}

}