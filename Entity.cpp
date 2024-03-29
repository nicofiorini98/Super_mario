#include "Entity.h"
#include "Game.h"
#include "Mario.h"
#include "Coin.h"
#include "Iceberg.h"
#include "Collectable.h"
#include "Pipe.h"
#include "Enemy.h"
#include "HiddenBlock.h"
#include "Muncher.h"
#include "GoalRoulette.h"
#include "FireBall.h"
#include "BlooberBaby.h"
#include "BlooberNanny.h"
#include "Leaf.h"
#include "FireBallPiranha.h"
#include "BigBertha.h"
#include "Cheep.h"
#include "Plant.h"
#include "JumpBlock.h"

Entity::Entity() : Object()
{
	//physics parameters
	moving_speed = 1;
	jumping_speed = 3;
	falling_speed = 3;
	moving_speed_div = 2;     

	//flags
	dir		= RIGHT;
	moving  = true;	
	jumping = false;
	falling = true;			//we  can create entities in mid air and they will fall
	dead    = false;
	dying   = false;
	freezed = false;
	slow	= false;
	script_move = false;
	downhill    = false;

	//counters
	jump_counter		= 0;
	animation_counter   = 0;
	death_counter		= 0;
	falling_counter     = 0;
	

	//durations
	jumping_duration = 30;
	death_duration	 = 50;

	//others
	walkable_object = nullptr;
	animation_div	= 1;

}
void Entity::startJumping()
{
	//entity can jump only when it is not falling
	if(!falling && !jumping)
	{
		walkable_object = nullptr;          
		jumping			= true;
	}
}

void Entity::endJumping()
{
	if(jumping)
	{
		jumping		 = false;
		jump_counter = 0;
		falling = true;
	}
}

void Entity::advance()
{
	if (freezed)
		return;

	//NOTE: every moment is embedded in a prevPos=pos() ... solveCollisions block
	//this is the only way to check if movement does break the impenetrability hypothesis
	//if it does, we need to revert to previous position

	
	if (moving)
	{
		prevPos = pos();

		if (script_move)
		{
			//moving in the downhill
			if (downhill)
			{
				if (dir == RIGHT)
				{
					setX(x() + moving_speed);
					setY(y() + moving_speed);
				}
				else if (dir == LEFT)
				{
					setY(y() - moving_speed);
					setX(x() - moving_speed);
				}
			}
			//moving in the uphill
			else
			{
				if (dir == RIGHT)
				{
					setX(x() + moving_speed);
					setY(y() - moving_speed);
				}
				else if (dir == LEFT)
				{
					setX(x() - moving_speed);
					setY(y() + moving_speed);
				}
			}
		}
		else
		{
			//slow mode: move 1 pixel every moving_speed_div frames
			if (slow)
				moving_speed = animation_counter % moving_speed_div == 0;

			if (dir == RIGHT)
				setX(x() + moving_speed);
			else if (dir == LEFT)
				setX(x() - moving_speed);
			else if (dir == UP)
				setY(y() - moving_speed);
			else if (dir == DOWN)
				setY(y() + moving_speed);
		}

		solveCollisions();
	}

	if (jumping)
    {
        prevPos = pos();

        //move upwards
        setY(y() - jumping_speed);

        //increase jump frame count
        if (jumping_speed < 0)
            jump_counter -= jumping_speed;
        else 
            jump_counter += jumping_speed;

        //end jumping when frame count reaches the defined limit
        if (jump_counter > jumping_duration)
            endJumping();

        solveCollisions();
    }

	bool aux = false;
	
	if (level_name == "World 6-9-2" && dynamic_cast<Mario*>(this)->getPower() >= 2 && pos().x() >= 49 * 16 && pos().x()<=54*16)
	{
		aux = true;
	}
	//if the entity is not touching its walkable object anymore
	//we have to start falling
	if ( walkable_object && !touchingDirection(walkable_object) && !aux)
	{
		
		walkable_object = nullptr;
		script_move = false;

		if (Game::instance()->getCurState() == "RUNNING")
			falling = true;
	}

	//falling
	if (falling)
	{
		prevPos = pos();		

		setY(y() + falling_speed);

		falling_counter++;
		
		solveCollisions();
	}
	
	//if we fall beyond the second scene bottom limit
	//we have to die (if not dying already)
	if ( level_name=="World 6-9-2" && y()>=28*16 && !dying)
		die();	
}

void Entity::animate()
{
	//increase animation counter
	animation_counter++;

	//increase death counter if dying
	if(dying && !dead)
	{
		death_counter++;
		if (death_counter >= death_duration)
			Entity::die();
	}
}

void Entity::solveCollisions()
{
	//if the entity cannot collide or is 100% dead, we avoid
	//solving possible collision
	if (!collidable || dead)
		return;

	//get collision
	QList<QGraphicsItem*> colliding_items = collidingItems();         

	//will be set to true if we collide an impenetrable object
	bool revert = false;
	bool touching_correction = true;

	Direction coll_dir;

	//manage collisions
	for (auto& ci : colliding_items)
	{
		Object* obj = dynamic_cast<Object*>(ci);
		if (!obj)
			continue;
		{
			//ignore collision if obj is not collidable
			if (!obj->isCollidable())
				continue;

			//ignore collision between Leaf and Inert
			if ((dynamic_cast<Leaf*>(this) && dynamic_cast<Inert*>(obj)) ||
				(dynamic_cast<Inert*>(this) && dynamic_cast<Leaf*>(obj)))
				continue;
			
			
			
			//ignore collisions between Collectables and Enemies
			if ((dynamic_cast<Collectable*>(this) && dynamic_cast<Enemy*>(obj)) && !dynamic_cast<Muncher*>(obj) ||
				(dynamic_cast<Enemy*>(this) && dynamic_cast<Collectable*>(obj)))
				continue;

			if ((dynamic_cast<Mushroom*>(this) && dynamic_cast<Coin*>(obj)) || 
				(dynamic_cast<Coin*>(this) && dynamic_cast<Mushroom*>(obj)))
				continue;
			
			//ignore collisions between two Collectables
			if (dynamic_cast<Collectable*>(this) && dynamic_cast<Collectable*>(obj))
				continue;
			
			//ignore collision between Plant and Inert
			if ((dynamic_cast<Plant*>(this) && dynamic_cast<Inert*>(obj)) ||
				(dynamic_cast<Plant*>(obj) && dynamic_cast<Inert*>(this)))
				continue;

			//ignore collision between Plant and Inert
			if ((dynamic_cast<Plant*>(this) && dynamic_cast<Mario*>(obj)))
				continue;

			
			
			if ((dynamic_cast<BigBertha*>(this) && dynamic_cast<Inert*>(obj)) ||
				(dynamic_cast<BigBertha*>(obj) && dynamic_cast<Inert*>(this)))
				continue;

			//ignore collision with BabyCheep and Inert
			if ((dynamic_cast<BabyCheep*>(this) && dynamic_cast<Inert*>(obj)) ||
				(dynamic_cast<BabyCheep*>(obj) && dynamic_cast<Inert*>(this)))
				continue;

			//ignore collision with Cheep and Inert
			if ((dynamic_cast<Cheep*>(this) && dynamic_cast<Inert*>(obj)) ||
				(dynamic_cast<Cheep*>(obj) && dynamic_cast<Inert*>(this)))
				continue;
			
			//ignore collision with Bloober baby and Inert
			if ((dynamic_cast<BlooberBaby*>(this) && !dynamic_cast<Inert*>(obj)) ||
				(dynamic_cast<BlooberBaby*>(obj) && dynamic_cast<Inert*>(this)))
				continue;

			//ignore collision with Bloober baby and fireball
			if ((dynamic_cast<BlooberBaby*>(this) && !dynamic_cast<FireBall*>(obj)) ||
				(dynamic_cast<BlooberBaby*>(obj) && dynamic_cast<FireBall*>(this)))
				continue;

			
			//ignore collision between Enemy and Enemy
			if ((dynamic_cast<Enemy*>(this) && dynamic_cast<Enemy*>(obj)))
				continue;

			//ignore collision with enemy when mario is injured
			if (dynamic_cast<Mario*>(this) && dynamic_cast<Mario*>(this)->isInjured() && dynamic_cast<Enemy*>(obj))
				continue;
			if (dynamic_cast<Enemy*>(this) && dynamic_cast<Mario*>(obj) && dynamic_cast<Mario*>(obj)->isInjured())
				continue;

			//ignore collision with Fireball and mario
			if ((dynamic_cast<Mario*>(this) && dynamic_cast<FireBall*>(obj)) ||
				(dynamic_cast<Mario*>(obj) && dynamic_cast<FireBall*>(this)))
				continue;

			//ignore collision with FireballPiranha and mario
			if ((dynamic_cast<FireBallPiranha*>(this) && !dynamic_cast<Mario*>(obj)))
				continue;

			

			//ignore collision of a dying entity with anoter entity
			Entity* entity_obj = dynamic_cast<Entity*>(obj);
			if (entity_obj && (dying || entity_obj->isDying()))
				continue;
		}
		//get collision direction
		coll_dir = collisionDirection(obj);

		// if it is not possible to calculate it, we skip current collision
		// (e.g. this may happen if we have solved the collision earlier)
		if (!coll_dir)
			continue;

	    //manage corner-corner collision in outOfWater
		if (dynamic_cast<Mario*>(this) && !dynamic_cast<Mario*>(this)->isInWater() && coll_dir == UNDETERMINED
			&& !dynamic_cast<JumpBlock*>(obj))
		{
			if (falling)
			{
				touching_correction = false; 
				coll_dir = DOWN;
			}
			else if (!jumping && !falling)  
			{
				coll_dir = dir;
				setX(x() + (dir == RIGHT ? -2 : 2));
				falling = true;
			}
			else if (jumping && !moving)
			{
				if (moving)
				{
					coll_dir = UNDETERMINED;
					revert = true;
				}
				else
					coll_dir = UP;
			}
		}
		
		//manage corner-corner collision for bloober nanny
		else if (dynamic_cast<BlooberNanny*>(this) && coll_dir == UNDETERMINED)
		{
			if (!dynamic_cast<BlooberNanny*>(this)->isBlocked_up() && !dynamic_cast<BlooberNanny*>(this)->isBlocked_side())
				touching_correction = false;

			if (dynamic_cast<BlooberNanny*>(this)->isBlocked_up())
				coll_dir = UP;
			else if (dynamic_cast<BlooberNanny*>(this)->isBlocked_side())
				coll_dir = dir;
		}

		if (coll_dir == RIGHT || coll_dir == LEFT || coll_dir == UP)
			touching_correction = false;
		
		// special case 1: collision with a walkable inert object or a muncher while falling
		// ---> end falling and in the former case set walkable object
		Inert* inert_obj = dynamic_cast<Inert*>(obj);
		Muncher* muncher_obj = dynamic_cast<Muncher*>(obj);
		if (coll_dir == DOWN && falling && ((inert_obj && inert_obj->isWalkable()) || muncher_obj ))
		{
			
			falling = false;
			falling_counter = 0;
			if (inert_obj)
			{
				walkable_object = inert_obj;
			}
		}


		// special case 2 : collision with a hidden block  from left/right or while falling
		// ---> ignore
		Mario* mario = dynamic_cast<Mario*> (this);
		HiddenBlock* hidden_block_obj = dynamic_cast<HiddenBlock*>(obj);
		if ( mario && hidden_block_obj && hidden_block_obj->isActive() && ((coll_dir == LEFT || coll_dir == DOWN) || mario->isFalling()) )
			continue;

		//special case 3: collision with an object while jumping
		//--->end jumping
		if (coll_dir == UP && jumping)
		{
			Mario* mario = dynamic_cast<Mario*>(this);
			if (mario && mario->isUnderPipe(level_name) && Game::instance()->isKeyUpPressed())
			{
				mario->enterPipe(Direction::DOWN);
				continue;
			}
			else 
				if(!dynamic_cast<GoalRoulette*>(obj))
					endJumping();  
		}

		
		//the two objects hit each other
		obj->hit(this, inverse(coll_dir));
		this->hit(obj, coll_dir);

		//special case 4 : collision when mario is making an attack in raccoon mode
		//---->ignore collision 
		if (dynamic_cast<Mario*>(this) && dynamic_cast<Mario*>(this)->isRaccoonAttack())
			continue;
		

		
		//if we ended up here, it means we have to revert
		//to the previous position (impenetrability)
		if(dynamic_cast<Coin*>(obj))
			continue;

		//manage collision of bloober nanny for each object
		if (dynamic_cast<BlooberNanny*>(this))
		{
			//special case for bloober when hit with downhill2
			if (dynamic_cast<Iceberg*>(obj) && dynamic_cast<Iceberg*>(obj)->type() == "downhill2")
				setPos(prevPos);
			else
			{
				if (coll_dir == UP || coll_dir == DOWN)
					setY(prevPos.y());
				else
					setX(prevPos.x());
			}
		}
		revert = true;
	}

	//revert to previous position if needed
	if (revert && !dynamic_cast<BlooberNanny*>(this))
		setPos(prevPos);

	//touchdown correction
	//entity is on a walkable object but is not touching it!
	//(this occurs when the entity penetrates the walkable object,
	//in wich case the 'revert' operation will put it in mid-air)
	if (!script_move && touching_correction && revert && walkable_object && !collisionDirection(walkable_object))
	{
			// just moving down until entity touches the walkable
		int i = 0;
			while (touchingDirection(walkable_object) != DOWN && i<4)
			{
				i++;
				//static int correct_counter = 0;
				//printf("[%d] %s is correcting touchdown (y = %.3f, dir = %d)\n", correct_counter++, this->name().c_str(), y(), touchingDirection(walkable_object));
				setY(y() + 1);
			}
		if(i==4)
		
			setX(x() + (dir == RIGHT ? -2 : 2));
		
	}
}


void Entity::die()
{
	
	
	//only a full living entity can die
	if(!dead)
	{
		//cannot move
		moving = false;

		//dead
		dead = true;
	}
}