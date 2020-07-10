#include "BlooberBaby.h"

#include "Sprites.h"
#include "Sounds.h"


BlooberBaby::BlooberBaby(QPoint position, int _move_id) : Enemy()
{
	collidable = true;
	pos_in = position;
	move_id = _move_id;
	moving = false;
	script = false;
	script_counter = 0;
	script_duration = 1;
	// durations
	
	jumping_duration = 10;
	falling_duration = 10;
	// textures
	texture_nothing = Sprites::instance()->get("nothing");
	texture_swim[0] = Sprites::instance()->get("Bloober-Baby-0");
	texture_swim[1] = Sprites::instance()->get("Bloober-Baby-1");
	texture_swim[2] = Sprites::instance()->get("Bloober-Baby-2");
	texture_death = Sprites::instance()->get("Bloober-Baby-0").transformed(QTransform().scale(-1, 1));

	// set texture and correct y-coordinate w.r.t. texture height
	setPixmap(texture_swim[0]);
	setPos(position - QPoint(0, pixmap().height()));

	//set the proper Zvalue
	if(move_id == 1)
		setZValue(4);
	else if(move_id == 2)
		setZValue(3);
	else if(move_id == 3)
		setZValue(2);
	else if(move_id == 4)
		setZValue(1);
}

void BlooberBaby::advance()
{
	//bloober baby is controlled by bloobler nanny except when is in script mode
	//in script mode starts to moving separated by bloober nanny
	if (script)
	{
		script_counter++;
		
		if (falling || jumping)
		{
			Entity::advance();
			jumping_speed = animation_counter % 2 == 0;
			falling_speed = animation_counter % 2 == 0;
			if (falling_counter > falling_duration) 
			{
				jumping = true;
				falling = false;
				falling_counter = 0;
			}
		}
		if (script_counter < script_duration / 25)
		{
			if (move_id == 1)
				setPos(pos() + QPoint(-1, -1));
			else if(move_id==2)
				setPos(pos() + QPoint(+1, -1));
			else if(move_id==3)
				setPos(pos() + QPoint(+1, +1));
			else if(move_id==4)
				setPos(pos() + QPoint(-1, +1));
		}
		else if (script_counter >= script_duration / 25 && script_counter < script_duration / 25 + 8) 
		{
			moving_speed = script_counter % 2 == 0;
			if (move_id == 1)
				setPos(pos() + QPoint(-moving_speed, -1));
			else if (move_id == 2)
				setPos(pos() + QPoint(1, -moving_speed));
			else if (move_id == 3) 
			    setPos(pos() + QPoint(moving_speed,1));
			else if (move_id == 4)
			    setPos(pos() + QPoint(-1, moving_speed));
		}
		else if (script_counter >= script_duration / 25 + 8 && script_counter < script_duration / 25 + 16) {
			moving_speed = script_counter % 3 == 0;
			if (move_id == 1) 
			    setPos(pos() + QPoint(-moving_speed,-1));
			else if (move_id == 2)
			    setPos(pos() + QPoint(1,-moving_speed));
			else if (move_id == 3) 
			    setPos(pos() + QPoint(moving_speed,1));
			else if (move_id == 4) 
			    setPos(pos() + QPoint(-1,moving_speed));
		}
		else if (script_counter >= script_duration / 25 + 16 && script_counter < script_duration / 25 + 24) 
		{
			moving_speed = script_counter % 4 == 0;
			if (move_id == 1)
			    setPos(pos() + QPoint(-moving_speed,-1));
			else if (move_id == 2) 
			    setPos(pos() + QPoint(1,-moving_speed));
			else if (move_id == 3)
			    setPos(pos() + QPoint(moving_speed,1));
			else if (move_id == 4) 
			    setPos(pos() + QPoint(-1,moving_speed));
		}
		else if (script_counter >= script_duration / 25 + 24 && script_counter < script_duration / 25 + 40) 
{
			if (move_id == 1)
			    setY(y() - 1);
			else if (move_id == 2)
			    setX(x() + 1);
			else if (move_id == 3) 
			    setY(y() + 1);
			else if (move_id == 4) 
			    setX(x() - 1);
}
		else if (script_counter >= script_duration / 25 + 40 && script_counter < script_duration / 25 + 48)
 {
			moving_speed = script_counter % 6 == 0;
			
			if (move_id == 1) 
			    setPos(pos() + QPoint(moving_speed,-1));
			else if (move_id == 2) 
			    setPos(pos() + QPoint(1,moving_speed));
			else if (move_id == 3)
			    setPos(pos() + QPoint(-moving_speed,1));
			else if (move_id == 4)
			    setPos(pos() + QPoint(-1,-moving_speed));
		}
		else if (script_counter >= script_duration / 25 + 48 && script_counter < script_duration / 25 + 56) 
{
			moving_speed = script_counter % 5 == 0;
			if (move_id == 1) 
			    setPos(pos() + QPoint(moving_speed,-1));
			else if (move_id == 2) 
			    setPos(pos() + QPoint(1,moving_speed));
			else if (move_id == 3) 
			    setPos(pos() + QPoint(-moving_speed,1));
			else if (move_id == 4)
			    setPos(pos() + QPoint(-1,-moving_speed));
		}
		else if (script_counter >= script_duration / 25 + 56 && script_counter < script_duration / 25 + 64) {
			moving_speed = script_counter % 4 == 0;
			if (move_id == 1) 
			    setPos(pos() + QPoint(moving_speed,-1));
			else if (move_id == 2) 
			    setPos(pos() + QPoint(1,moving_speed));
			else if (move_id == 3) 
			    setPos(pos() + QPoint(-moving_speed,1));
			else if (move_id == 4)
			    setPos(pos() + QPoint(-1,-moving_speed));
		}
		else if (script_counter >= script_duration / 25 + 64 && script_counter < script_duration / 25 + 72) 
		{
			moving_speed = script_counter % 3 == 0;
			if (move_id == 1) 
			    setPos(pos() + QPoint(moving_speed,-1));
			else if (move_id == 2) 
			    setPos(pos() + QPoint(1,moving_speed));
			else if (move_id == 3) 
			    setPos(pos() + QPoint(-moving_speed,1));
			else if (move_id == 4) 
			    setPos(pos() + QPoint(-1,-moving_speed));
		}
		else if (script_counter >= script_duration / 25 + 72 && script_counter < script_duration / 25 + 80) 
		{
		    moving_speed = script_counter % 2 == 0;
			if (move_id == 1) 
			    setPos(pos() + QPoint(moving_speed,-1));
			else if (move_id == 2) 
			    setPos(pos() + QPoint(1,moving_speed));
			else if (move_id == 3) 
			    setPos(pos() + QPoint(-moving_speed,1));
			else if (move_id == 4) 
			    setPos(pos() + QPoint(-1,-moving_speed));
		}
		else if (script_counter >= script_duration / 25 + 80 && script_counter < script_duration / 25 + 88)
		{
			if (move_id == 1) 
			    setPos(pos() + QPoint(1,-1));
			else if (move_id == 2)
				setPos(pos() + QPoint(1,1));
            else if (move_id == 3) 
				setPos(pos() + QPoint(-1,1));
            else if (move_id == 4) 
				setPos(pos() + QPoint(-1,-1));
        }
		else if (script_counter >= script_duration / 25 + 88 && script_counter < script_duration / 25 + 96) 
		{
		    moving_speed = script_counter % 2 == 0;
			if (move_id == 1) 
			    setPos(pos() + QPoint(1,-moving_speed));
			else if (move_id == 2) 
			    setPos(pos() + QPoint(moving_speed,1));
			else if (move_id == 3)
			    setPos(pos() + QPoint(-1,moving_speed));
			else if (move_id == 4) 
			    setPos(pos() + QPoint(-moving_speed,-1));
		}
		else if (script_counter >= script_duration / 25 + 96 && script_counter < script_duration / 25 + 104) 
		{
		    moving_speed = script_counter % 3 == 0;
			if (move_id == 1) 
			    setPos(pos() + QPoint(1,-moving_speed));
			else if (move_id == 2) 
			    setPos(pos() + QPoint(moving_speed,1));
			else if (move_id == 3)
			     setPos(pos() + QPoint(-1,moving_speed));
			else if (move_id == 4) 
			     setPos(pos() + QPoint(-moving_speed,-1));
		}
		else if (script_counter >= script_duration / 25 + 104 && script_counter < script_duration / 25 + 112) 
		{
		    moving_speed = script_counter % 4 == 0;
			if (move_id == 1) 
			    setPos(pos() + QPoint(1,-moving_speed));
			else if (move_id == 2) 
			    setPos(pos() + QPoint(moving_speed,1));
			else if (move_id == 3)
			     setPos(pos() + QPoint(-1,moving_speed));
			else if (move_id == 4) 
			     setPos(pos() + QPoint(-moving_speed,-1));
		}
		else if (script_counter >= script_duration / 25 + 112 && script_counter < script_duration / 25 + 120) 
		{
		    moving_speed = script_counter % 5 == 0;
			if (move_id == 1) 
			    setPos(pos() + QPoint(1,-moving_speed));
			else if (move_id == 2) 
			    setPos(pos() + QPoint(moving_speed,1));
			else if (move_id == 3)
			     setPos(pos() + QPoint(-1,moving_speed));
			else if (move_id == 4) 
			     setPos(pos() + QPoint(-moving_speed,-1));
		}
		else if (script_counter >= script_duration / 25 + 120 && script_counter < script_duration / 25 + 128) 
		{
		    moving_speed = script_counter % 6 == 0;
			if (move_id == 1) 
			    setPos(pos() + QPoint(1,-moving_speed));
			else if (move_id == 2) 
			    setPos(pos() + QPoint(moving_speed,1));
			else if (move_id == 3)
			     setPos(pos() + QPoint(-1,moving_speed));
			else if (move_id == 4) 
			     setPos(pos() + QPoint(-moving_speed,-1));
		}
		else if (script_counter >= script_duration / 25 + 128 && script_counter < script_duration / 25 + 144)
		{
			if (move_id == 1) 
			    setX(x() + 1);
			else if (move_id == 2) 
			    setY(y() + 1);
			else if (move_id == 3) 
			    setX(x() - 1);
			else if (move_id == 4)
			    setY(y() - 1);
		}
		else if (script_counter >= script_duration / 25 + 144 && script_counter < script_duration / 25 + 152) 
		{
		    moving_speed = script_counter % 6 == 0;
			if (move_id == 1) 
			    setPos(pos() + QPoint(1,moving_speed));
			else if (move_id == 2) 
			    setPos(pos() + QPoint(-moving_speed,1));
			else if (move_id == 3)
		 	    setPos(pos() + QPoint(-1,-moving_speed));
			else if (move_id == 4) 
			    setPos(pos() + QPoint(moving_speed,-1));
        }
		else if (script_counter >= script_duration / 25 + 152 && script_counter < script_duration / 25 + 160)
		{
		    moving_speed = script_counter % 5 == 0;
			if (move_id == 1) 
			    setPos(pos() + QPoint(1,moving_speed));
			else if (move_id == 2) 
			    setPos(pos() + QPoint(-moving_speed,1));
			else if (move_id == 3)
		 	    setPos(pos() + QPoint(-1,-moving_speed));
			else if (move_id == 4) 
			    setPos(pos() + QPoint(moving_speed,-1));
		}
		else if (script_counter >= script_duration / 25 + 160 && script_counter < script_duration / 25 + 168) 
		{
		    moving_speed = script_counter % 4 == 0; 
			if (move_id == 1) 
			    setPos(pos() + QPoint(1,moving_speed));
			else if (move_id == 2) 
			    setPos(pos() + QPoint(-moving_speed,1));
			else if (move_id == 3)
		 	    setPos(pos() + QPoint(-1,-moving_speed));
			else if (move_id == 4) 
			    setPos(pos() + QPoint(moving_speed,-1));
		}
		else if (script_counter >= script_duration / 25 + 168 && script_counter < script_duration / 25 + 176) 
		{
		    moving_speed = script_counter % 3 == 0;
			if (move_id == 1) 
			    setPos(pos() + QPoint(1,moving_speed));
			else if (move_id == 2) 
			    setPos(pos() + QPoint(-moving_speed,1));
			else if (move_id == 3)
		 	    setPos(pos() + QPoint(-1,-moving_speed));
			else if (move_id == 4) 
			    setPos(pos() + QPoint(moving_speed,-1));
		}
		else if (script_counter >= script_duration / 25 + 176 && script_counter < script_duration / 25 + 184) 
		{
		    moving_speed = script_counter % 2 == 0;
			if (move_id == 1) 
			    setPos(pos() + QPoint(1,moving_speed));
			else if (move_id == 2) 
			    setPos(pos() + QPoint(-moving_speed,1));
			else if (move_id == 3)
		 	    setPos(pos() + QPoint(-1,-moving_speed));
			else if (move_id == 4) 
			    setPos(pos() + QPoint(moving_speed,-1));
		}
		else if (script_counter >= script_duration / 25 + 184 && script_counter < script_duration / 25 + 192) 
		{
			if (move_id == 1) 
			    setPos(pos() + QPoint(1,1));
			else if (move_id == 2)
				setPos(pos() + QPoint(-1,1));
            else if (move_id == 3) 
				setPos(pos() + QPoint(-1,-1));
            else if (move_id == 4) 
				setPos(pos() + QPoint(1,-1));
		}
		else if (script_counter > script_duration) 
		{
			script = false;
			die();
		}
	}
	solveCollisions();
}


void BlooberBaby::animate()
{
	Entity::animate();

	// set the proper texture
	if (dying)
		setPixmap(texture_death);
	if (jumping)
		setPixmap(texture_swim[1]);
	else if (falling)
		setPixmap(texture_swim[0]);

	if (script_counter > script_duration / 25 + 152 && script_counter < script_duration)
	{
		if (animation_counter % 3 == 0)
			setPixmap(texture_nothing);
	}
}

void BlooberBaby::hit(Object* what, Direction fromDir)
{
	Object::hit(what, fromDir);
}








	