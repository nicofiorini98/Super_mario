#include "BlooberNanny.h"
#include "Game.h"
#include "Splash.h"
#include "Sprites.h"
#include "Sounds.h"
#include <iostream>
#include "Iceberg.h"

BlooberNanny::BlooberNanny(QPoint position, Direction direction) : Enemy()
{
    //get mario
    mario = Game::instance()->getMario();

	first = false;

	//set bloober without babies
    baby1 = nullptr;
    baby2 = nullptr;
    baby3 = nullptr;
    baby4 = nullptr;

	
    // set attribute
    over_head    = false;
    near_head    = false;
    under_head   = false;
    splash       = false;
    blocked_up   = false;
    blocked_side = false;
    slow         = false;
    falling      = false;
    jumping      = false;
    moving       = false;
    spawn_baby = true;
    launch_baby = false;

    pos_in = position;
    dir    = direction;
   
    // set counter
    moving_start_counter = -1;
    moving_stop_counter = -1;
    animation_div = 16;

    previous_pos = 0;
    spawn_counter = 0;
    spawn_duration = 500;
    launch_counter = 0;
    wait_counter = -1;
    jumping_speed = 1;
    falling_speed=1;
	
    // durations
    death_duration = 400;
    jumping_duration = 32; 
    moving_start_counter = -1;
	
    // textures
    texture_swim[0] = Sprites::instance()->get("Bloober-Nanny-0");
    texture_swim[1] = Sprites::instance()->get("Bloober-Nanny-1");
	
    //texture bloober attack with babies
	texture_launch[0]= Sprites::instance()->get("Bloober-Nanny-1");
    texture_launch[1] = Sprites::instance()->get("Bloober-Nanny-2");
	
    texture_death = Sprites::instance()->get("Bloober-Nanny-0").transformed(QTransform().scale(1, -1));

    // set texture and correct y-coordinate w.r.t. texture height
    setPixmap(texture_swim[0]);
    setPos(position - QPoint(0, pixmap().height()));
    setZValue(5);

}


void BlooberNanny::advance()
{
    //when mario goes out of sight of the bloober, then bloober is freezed
    if ((mario->pos().x() >= pos().x() + 16 * 16 || mario->pos().x() <= pos().x() - 16 * 16)
        || (mario->pos().y() >= pos().y() + 10 * 16 || mario->pos().x() <= pos().x() - 12 * 16))
        freezed = true;
    else
        freezed = false;

    if (freezed)
        return;

	//increase previous_pos counter for set the position of the baby
    if (previous_pos >= 0)
    {
        if (previous_pos == 40)
            previous_pos = 0;

        nframe_prev_pos[previous_pos] = pos().toPoint();
        previous_pos++;
    }

    //when bloober nanny has the babies, and the babies isn't free to move
    //set position of the baby for each frame
    if (baby1 && !baby1->getScript_Move())
        baby1->setPos(posBaby(1));
    if (baby2 && !baby2->getScript_Move())
        baby2->setPos(posBaby(2));
    if (baby3 && !baby3->getScript_Move())
        baby3->setPos(posBaby(3));
    if (baby4 && !baby4->getScript_Move())
        baby4->setPos(posBaby(4));

	
    //bounce and fall in the depth when dying
    if (dying)
    {
        prevPos = pos();

    	//bounce and fall in the depth
        if (death_counter >= 0 && death_counter <= 20)
            setY(y() - (animation_counter % 2));
        else
            setY(y() + 1);

    	//horizontal moving in dying
        if (animation_counter % 16 == 0)
            setX(x() + 1);
        else if (animation_counter % 16 == 4)
            setX(x() + 1);
        else if (animation_counter % 16 == 8)
            setX(x() - 1);
    	 else if (animation_counter % 16 == 12)
            setX(x() - 1);

        if (death_counter == 1)
        {
        	if(baby1)
				baby1->setDying(true);
        	if(baby2)
				baby2->setDying(true);
        	if(baby3)
				baby3->setDying(true);
        	if(baby4)
			    baby4->setDying(true);
        }
    	//before die(), kill the own babies and forget it
    	if(death_counter>=350)
    	{
    		
            if (baby1)
            {
                baby1->die();
                baby1 = nullptr;
            }
    		if (baby2)
            {
                baby2->die();
                baby2 = nullptr;
            }
    		if (baby3)
            {
                baby3->die();
                baby3 = nullptr;
            }
    		if (baby4)
            {
                baby4->die();
                baby4 = nullptr;
            }
    	}
    	
        return;
    }

	//get the flag for choose which script to do,
	//bloober want to stay on the mario's head
    if (!moving || (script_counter == script_duration && !over_head) || (moving && over_head))
    {
    
        if (pos().y() < mario->pos().y() - 18) //bloober is over mario's head
        {
            if (over_head)
                script_counter++;
            else
            {
                near_head = false;
                under_head = false;
                over_head = true;

                moving_start_counter = 0;
                script_counter = 0;
                script_duration = 0;
            }
        }
        else if (pos().y() == mario->pos().y() - 18) //bloober is near mario's head
        {
            near_head = true;
            under_head = false;
            over_head = false;

            moving_start_counter = 0;
            script_counter = 0;
            script_duration = 64;
        }
        else if (pos().y() > mario->pos().y() - 18) //bloober is under mario's head 
        {
            near_head = false;
            under_head = true;
            over_head = false;

            moving_start_counter = 0;
            script_counter = 0;
            script_duration = 48;
        }
    	//go in the same direction of mario
        dir = (mario->getDirection() == RIGHT ? RIGHT : LEFT);

        //script move to do is taken, then start to move
        moving = true;
    }
   
	
    //when bloober doesn't have all the babies,it creates other
    if (spawn_baby)
    {
        spawn_counter++;

        if (spawn_counter == 50)
            baby1 = new BlooberBaby(posBaby(1), 1);
        else if (spawn_counter == 200)
            baby2 = new BlooberBaby(posBaby(2), 2);
        else if (spawn_counter == 300)
            baby3 = new BlooberBaby(posBaby(3), 3);
        else if (spawn_counter == 400)
            baby4 = new BlooberBaby(posBaby(4), 4);

        else if (spawn_counter == 800) //go to launch baby mode
        {
            spawn_baby = false;
            launch_baby = true;
            launch_counter = 0;
        }
    }

	//when bloober has all the baby, attack mario with all the babies
	if(launch_baby)
	{
        launch_counter++;
		moving = false; 

        if (launch_counter > 80 )
        {
            baby1->setScript_Move(true);
            baby1 = nullptr;
            baby2->setScript_Move(true);
            baby2 = nullptr;
            baby3->setScript_Move(true);
            baby3 = nullptr;
            baby4->setScript_Move(true);
            baby4 = nullptr;
        	//go to spawn baby modes
            launch_baby = false;
            moving = true; 
            spawn_baby  = true;
            spawn_counter = 0;
        }
	}
	//if bloober know the script to do, then do it
    if(moving)
    {
    	//manage the movement to do when is under the head of mario
        if(!over_head)
        {
        	//lateral move for 32 frames then start falling
            if (script_counter % script_duration  < 32)
            {
                jumping      = true;
                falling      = false;
            }
            else  
            {
                jumping     = false;
                falling     = true;
            	
            	//reset flag collision detection
                blocked_up  = false;
                blocked_side= false;
            }
        }
        else  // when is overhead, bloober can only fall
        {
            jumping      = false;
            falling      = true;
        	
        	//reset flag collision detection
            blocked_up   = false;
            blocked_side = false;
        }

    	//manage physic parameters when jumping
        if (jumping)
        {
        	//wen bloober is in the surface of water, then is blocked and create a splash
            if (pos().y() <= 16 * 16)
            {
                blocked_up = true;
                if (!splash)
                {
                    splash = true;
                    new Splash(pos().toPoint());
                }
            }
            else
                splash = false;
        	
            prevPos = pos();

        	//jumping accelleration during the script
        	if (script_counter <= 8)                                //0.5 speed
                jumping_speed = moving_start_counter % 2;
            else if (script_counter > 8 && script_counter <= 12)
                jumping_speed = 1;                                  //1 speed
            else if (script_counter > 12 && script_counter <= 24)
                jumping_speed = moving_start_counter % 2 + 1;      //1.5 speed
            else if (script_counter > 24)
                jumping_speed = moving_start_counter % 2;           //0.5 speed

            moving_start_counter++;
        	
            //start to wait bloober baby for 10 frames
            if (wait_counter < 0 && script_counter == 31)
                wait_counter = 0;
            
            if (wait_counter >= 0 && wait_counter < 8)
            {
                wait_counter++;
                jumping_speed = 0;
            }
            else if (wait_counter >= 8)
            {
                wait_counter = -1;
                script_counter ++;
                jumping_speed = 0;
            }

        	script_counter += jumping_speed;

            if (dir == RIGHT)
                setX(x() + jumping_speed);
            else if(dir == LEFT)
                setX(x() - jumping_speed);
        	if(!blocked_up)
				setY(y() - jumping_speed);
        	
            solveCollisions(); 
        }

    	//manage physic parameters when falling
        if (falling && !over_head )
        {
            prevPos = pos();	
            
            if(script_counter <= 36)                                //0.25 speed
                falling_speed = moving_start_counter % 4 == 0;

            else if (script_counter > 36 && script_counter <= 40)
                falling_speed = moving_start_counter % 2;           //0.5 speed

            else if (script_counter >= 40)                          // 0.75 speed
                falling_speed=moving_start_counter % 4 !=0;

            moving_start_counter++;

            setY(y() + falling_speed);

            script_counter += falling_speed;
            solveCollisions();
        }

        else if(falling && over_head)
        {
            prevPos = pos();

			falling_speed = 1;
        	
            setY(y() + falling_speed);
        	
            solveCollisions();
        }
    }
}


void BlooberNanny::animate()
{
	//spawn baby the first time
    if (animation_counter == 333)
        spawn_baby = true;


    //set the proper texture
    if (falling)
        setPixmap(texture_swim[1]);
    else if (jumping && script_counter > 3)
        setPixmap(texture_swim[0]);

    if (launch_baby)
        setPixmap(texture_launch[(animation_counter / 4) % 2]);

    if(dying)
        setPixmap(texture_death);
	
    Entity::animate();
	
}

void BlooberNanny::hit(Object* what, Direction fromDir)
{
    Object::hit(what, fromDir);

    if(dynamic_cast<Inert*>(what) && fromDir == UP)
        blocked_up = true;
    if(dynamic_cast<Inert*>(what) && (fromDir == RIGHT || fromDir == LEFT))
        blocked_side = true;
}

void BlooberNanny::hurt()
{
    Sounds::instance()->play("stomp");
    dying = true;
    moving = false;
    mario->updateScore(100, pos().toPoint());
} 

QPoint BlooberNanny::posBaby(int id)
{

    int aux;
    //memorize the previous of the bloober for give to the babies
    if (id == 1)
    {
        if (previous_pos - 10 >= 0)
            aux = previous_pos - 10;
        else
            aux = 40 + (previous_pos - 10);

        return (nframe_prev_pos[aux] + QPoint(4, 0));
    }
    else if (id == 2)
    {
        if (previous_pos - 20 >= 0)
            aux = previous_pos - 20;
        else
            aux = 40 + (previous_pos - 20);

        return (nframe_prev_pos[aux] + QPoint(4, 0));
    }
    else if (id == 3)
    {
        if (previous_pos - 30 >= 0)

            aux = previous_pos - 30;
        else

            aux = 40 + (previous_pos - 30);

        return (nframe_prev_pos[aux] + QPoint(4, 0));
    }
    else
    {
        if (previous_pos - 40 >= 0)
            aux = previous_pos - 40;
        else
            aux = 40 + (previous_pos - 40);

        return (nframe_prev_pos[aux] + QPoint(4, 0));
    }
}

QPainterPath BlooberNanny::shape() const
{
    QPainterPath path;
    path.addRect(3, boundingRect().top() + 3 , boundingRect().width() -6,boundingRect().bottom() -3);
    return path;
}