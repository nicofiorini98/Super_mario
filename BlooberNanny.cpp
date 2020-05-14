#include "BlooberNanny.h"
#include "Game.h"
#include "Splash.h"
#include "Sprites.h"
#include "Sounds.h"
#include <iostream>
#include "Iceberg.h"

BlooberNanny::BlooberNanny(QPoint position, Direction direction) : Enemy()
{
    mario = Game::instance()->getMario();

    baby1 = nullptr;
    baby2 = nullptr;
    baby3 = nullptr;
    baby4 = nullptr;

    counter_pos = 0;
	
    // set attribute
    over_head    = false;
    near_head    = false;
    under_head   = false;

    splash = false;

    blocked_up   = false;
    blocked_side = false;

    slow         = false;
    falling      = false;
    jumping      = false;
    moving       = false;

    pos_in = position;
    dir    = direction;
    //counter_movement = -2; // dovra' essere cambiata questa variabile, poi ci penso quando ho chiaro il movimento che deve fare
    //dovra essere maggiore di 0 quando mario sara' vicino alla medusa

    // set counter
    moving_start_counter = -1;
    moving_stop_counter = -1;
    animation_div = 16;
	
	//lancio dei bambini
    spawn_baby = true;
    spawn_counter = 0;
    spawn_duration = 500;
    launch_baby = false;
    launch_counter = 0;
    wait_counter = -1;

    jumping_speed = 1;
    falling_speed=1;
	
    // durations
    death_duration = 100;
    jumping_duration = 32; // tanto il movimento laterale e' sempre di 32 pixel
    moving_start_counter = -1;
    // textures
    texture_swim[0] = Sprites::instance()->get("Bloober-Nanny-0");
    texture_swim[1] = Sprites::instance()->get("Bloober-Nanny-1");
    //texture bloober attack with babies
	texture_launch[0]= Sprites::instance()->get("Bloober-Nanny-1");
    texture_launch[1] = Sprites::instance()->get("Bloober-Nanny-2");
	
    texture_death = Sprites::instance()->get("Bloober-Nanny-0").transformed(QTransform().scale(-1, 1));

    // set texture and correct y-coordinate w.r.t. texture height
    setPixmap(texture_swim[0]);
    setPos(position - QPoint(0, pixmap().height()));
    setZValue(5);

}


void BlooberNanny::advance()
{
	
    if (!moving || (script_counter == script_duration && !over_head) || (moving && over_head))
    {
    	
       /* if ((mario->pos().y() - pos().y()) >= 16 * 8 && (mario->pos().x() - pos().x()) >= 16 * 10)
        {
            moving = false;                 
            return;					
        }*/

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
    
    if (counter_pos >= 0)
    {
        if (counter_pos == 40)
            counter_pos = 0;
    	
        nframe_prev_pos[counter_pos] = pos().toPoint();
        counter_pos++;
    }
	
    //spawn baby modes
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
    //launch baby modes
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
    if(moving)
    {
    	
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
        else  // is overhead, i can only fall
        {
            jumping      = false;
            falling      = true;
        	//reset flag collision detection
            blocked_up   = false;
            blocked_side = false;
        }

    	//todo riniziare a commentare bene da qui
        if (jumping)
        {
            if (pos().y() <= 16 * 16)
            {
                blocked_up = true;
                splash = true;
            }
        	
            prevPos = pos();

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
            solveCollisions();//questo solve collision mi rimandera' nel hit, mi conviene utilizzarlo
        }

        else if(falling && over_head)
        {
            prevPos = pos();

			falling_speed = 1;
        	
            setY(y() + falling_speed);
        	
            solveCollisions();
        }
    }
	
	//when bloober nanny has the babies, and the babies isn't free to move
	//set position of the baby for each frame
    if(baby1 && !baby1->getScript_Move())
		baby1->setPos(posBaby(1));
	if(baby2 && !baby2->getScript_Move())
		baby2->setPos(posBaby(2));
	if(baby3 && !baby3->getScript_Move())
		baby3->setPos(posBaby(3));
	if(baby4 && !baby4->getScript_Move())
		baby4->setPos(posBaby(4));
}


void BlooberNanny::animate()
{
    if (animation_counter == 333)
        spawn_baby = true;
	
    if (falling)
        setPixmap(texture_swim[1]);
    else if (jumping && script_counter > 3)
        setPixmap(texture_swim[0]);

    if (launch_baby)
        setPixmap(texture_launch[(animation_counter / 4) % 2]); //texture lampeggianti

    if(dying)
        setPixmap(texture_death);

    //lo richiamo perchè mi serve per far morire la medusa
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
    moving = false;  // todo da togliere quando faccio la morte 
} 



QPoint BlooberNanny::posBaby(int id)
{
    //counter_pos, è la posizione corrente della medusa
    if (id == 1)
    {
        if (counter_pos - 10 >= 0)
            counter_pos1 = counter_pos - 10;
        else
            counter_pos1 = 40 + (counter_pos - 10);

        return (nframe_prev_pos[counter_pos1] + QPoint(4, 0));
    }
    else if (id == 2)
    {
        if (counter_pos - 20 >= 0)
            counter_pos1 = counter_pos - 20;
        else
            counter_pos1 = 40 + (counter_pos - 20);

        return (nframe_prev_pos[counter_pos1] + QPoint(4, 0));
    }
    else  if (id == 3)
    {
        if (counter_pos - 30 >= 0)
            counter_pos1 = counter_pos - 30;
        else
            counter_pos1 = 40 + (counter_pos - 30);

        return (nframe_prev_pos[counter_pos1] + QPoint(4, 0));
    }
    else  if (id == 4)
    {
        if (counter_pos - 40 >= 0)
            counter_pos1 = counter_pos - 40;
        else
            counter_pos1 = 40 + (counter_pos - 40);

        return (nframe_prev_pos[counter_pos1] + QPoint(4, 0));
    }
}


QPainterPath BlooberNanny::shape() const
{
    QPainterPath path;
    path.addRect(3, boundingRect().top() + 3 , boundingRect().width() -6,boundingRect().bottom() -3);
    return path;
}