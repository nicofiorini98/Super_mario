#include <iostream>
#include <stdlib.h>
#include "BigBertha.h"
#include "Game.h"
#include <iostream>
#include "Sprites.h"
#include "Sounds.h"


BigBertha::BigBertha(QPoint position, Direction direction) : Enemy()
{
    dir = direction;
    //set default flags
    slow = true;
    launch_baby = false;

	//counter
    script_counter  = 0;
    moving_start_counter = 0;
    stopped_start_counter = 0;
	
    // durations 
    death_duration = 300;
    script_duration = 116;

    // textures
    texture_swim_close[0] = Sprites::instance()->get("big-bertha-3");
    texture_swim_close[1] = Sprites::instance()->get("big-bertha-2");
    texture_swim_open[0] = Sprites::instance()->get("big-bertha-1");
    texture_swim_open[1] = Sprites::instance()->get("big-bertha-0");
    texture_death = Sprites::instance()->get("big-bertha-0").transformed(QTransform().scale(1, -1));

    baby = new BabyCheep(position, dir);

    // set texture and correct y-coordinate w.r.t. texture height
    setPixmap(texture_swim_close[0]);
    setPos(position);
    setZValue(3);

}

void BigBertha::advance()  //vedere un po' come devo pensare big Bertha
{

	if(baby && baby->isDying())
	{
        baby = nullptr;
	}
    if (script_counter > script_duration) 
    {
    	//reset counter when the script finished
        script_counter=0;
        moving_start_counter = 0;

    	//choose whether to throw the baby in the following script
    	if(!baby)
            baby = new BabyCheep((pos() + QPoint(7, 13)).toPoint(), dir);
    	if(baby)
			launch_baby = rand() % 2;
        
    }

	//increase the counter
    if(moving_start_counter >= 0)
         moving_start_counter++;

	//bounce and fall in the depths when dying
    if(dying)
    {
        if(script_counter < 10)
        {
        	
            moving_speed = moving_start_counter % 2;
            setY(y()-moving_speed);
        }
        else if(script_counter >=8 && script_counter <24) // ho messo che il salto prima de affoga è 16, forse è più lungo, 32 mi sembra eccessivo
        {
            moving_speed = 1;
        	
            setY(y()-moving_speed);
        }
        else if(script_counter >=24 && script_counter <40)
        {
            moving_speed = moving_start_counter % 2;
            setY(y()+moving_speed);
        }
        else
        {
            moving_speed = 1;
            setY(y()+moving_speed);
        }
        script_counter += moving_speed;

        return; 
    }

	//script moving when don't launch the baby
    if(!launch_baby)
    {
    	//manage the moving_speed during the script
        if (script_counter < 16)
        {
            moving_speed = moving_start_counter % 4 != 0;  //0.75 speed
            script_counter += moving_speed;
        }
        else if (script_counter >= 16 && script_counter < 32) // 1 speed
        {
            moving_speed = 1;
            script_counter += moving_speed;
        }
        else if (script_counter >= 32 && script_counter < 96) // 1.33 speed max
        {
            moving_speed = (moving_start_counter % 3==0) +1;
            script_counter += moving_speed;
        }
        else if (script_counter >= 96 && script_counter < 104) //0.75 speed
        {
            moving_speed = moving_start_counter % 4 !=0;
            script_counter += moving_speed;
        }
        else if (script_counter == 104)
        {
        	//change direction when the edges is reached
            dir = inverse(dir);
            script_counter++;
        }
        else
        {
            moving_speed = moving_start_counter % 2; // 0.5 speed
            script_counter += moving_speed;
        }
    }
	//script move when needs to throw the baby
    else
    {
    	//manage the moving_speed during the script
        if(script_counter==0)
        {
            moving_speed=0;
            if(stopped_start_counter ==0)
            {
            	if(baby)
            	{
                    //make the baby visible and stop big bertha
                    baby->setZValue(3);
                    baby->setScript_Move(true, dir);
            	}
            	
                stopped_start_counter++;
            }
        	//increase blocked counter
            else if(stopped_start_counter >0 && stopped_start_counter <48)
                stopped_start_counter++;
        	//restart to moving big bertha
            else if(stopped_start_counter ==48)
            {
                script_counter++;
                stopped_start_counter =0;
            }
        }
        else if(script_counter>0 && script_counter < 16 ) // 0.5 speed
        {
            moving_speed = moving_start_counter % 2;
            script_counter += moving_speed;
        }
        else if (script_counter >= 16 && script_counter < 32)
        {
            moving_speed = moving_start_counter % 4 !=0 ;  //0.75 speed
            script_counter += moving_speed;
        }

        else if (script_counter >= 32 && script_counter < 48) // 1 speed
        {
            moving_speed = 1;
            script_counter += moving_speed;
        }
        else if (script_counter >= 48 && script_counter < 96) //1.33 speed
        {
            moving_speed = (moving_start_counter % 3 == 0) + 1;
            script_counter += moving_speed;
        }
        else if (script_counter >= 96 && script_counter < 104)//0.75 speed
        {
            moving_speed = moving_start_counter % 4 !=0 ;
            script_counter += moving_speed;
        }
        else if (script_counter == 104)
        {
        	//change direction when edges is reached
            setX(x() - 1);
            dir = inverse(dir);
            script_counter++;
        }
        else
        {
            moving_speed = moving_start_counter % 3 == 0 ;
            script_counter+=moving_speed;
        }
    }

	//
    if ( dir == RIGHT)
        setX(x() + moving_speed);
    else
        setX(x() - moving_speed);


	//make baby in the mouth of big bertha
	if(baby)
	{
        std::cout << "prima\n";
        if (!launch_baby)
        {
            baby->setZValue(1);
            baby->setPos(pos() + QPoint(7, 13));
        }
        else if (launch_baby && script_counter >= 41)
        {
            baby->setZValue(1);
            baby->setPos(pos() + QPoint(7, 13));
        }
        std::cout << "dopo\n";
	}
    

    //floating up and down during the time 
    if(moving_start_counter % 128 == 1 )
        setY(y()+1);
    if(moving_start_counter % 128 == 16 )
        setY(y()+1);
    if(moving_start_counter % 128 == 32 )
        setY(y()-1);
    if(moving_start_counter % 128 ==48 )
        setY(y()-1);
    if(moving_start_counter % 128 == 64 )
        setY(y()-1);
    if(moving_start_counter % 128 == 80 )
        setY(y()-1);
    if(moving_start_counter % 128 == 96 )
        setY(y()+1);
    if(moving_start_counter % 128 == 112 )
        setY(y()+1);
}

void BigBertha::animate()
{
    Entity::animate();

    // set the proper texture
    if (dying)
        setPixmap(texture_death);
    else if(!launch_baby)
        setPixmap(texture_swim_close[(animation_counter / 8) % 2]);
    else if(launch_baby && script_counter>=55)
        setPixmap(texture_swim_close[(animation_counter / 8) % 2]);
    else
        setPixmap(texture_swim_open[(animation_counter/8)%2]);


    if (dir == RIGHT)
        setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
}

void BigBertha::hit(Object* what, Direction fromDir)
{
    Object::hit(what, fromDir);

}

void BigBertha::hurt()
{
    Sounds::instance()->play("stomp");
    dying = true;
    script_counter=0;
    moving_start_counter = 0;
    script_duration = death_duration;

    if(baby && !baby->isScript_Move())
        baby->die();
    else
        baby->setBabyFree(true);

}