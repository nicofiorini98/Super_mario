#include <iostream>
#include <stdlib.h>
#include "BigBertha.h"
#include "Game.h"
#include <iostream>
#include "Sprites.h"
#include "Sounds.h"


BigBertha::BigBertha(QPoint position, Direction direction) : Enemy()
{
    //todo togliere il puntatore a mario se non miglioro la morte
    mario = Game::instance()->getMario();
    script_counter  = 0;
    blocked_counter = 0;
    script_duration = 116;    
    launch_baby = false;
    dir  = direction;
    slow = true;
    moving_start_counter = 0;
    // durations 
    death_duration = 300;

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

    if (script_counter > script_duration) 
    {
    	//reset counter when the script finished
        script_counter=0;
        moving_start_counter = 0;

    	//choose whether to throw the baby in the following script
        launch_baby = rand() % 2;

    	//todo vedere se serve
       /* if (!launch_baby)
            blocked_counter = 0;*/
    }

	//increase the counter
    if(moving_start_counter >= 0)
         moving_start_counter++;

	//bounce and fall in the depths when dying
    if(dying)
    {
    	
        if(death_counter < 10)
        {
            moving_speed = moving_start_counter % 2;
            setY(y()-moving_speed);
        }
        else if(death_counter >=8 && death_counter <24) // ho messo che il salto prima de affoga è 16, forse è più lungo, 32 mi sembra eccessivo
        {
            moving_speed = 1;
        	
            setY(y()-moving_speed);
        }
        else if(death_counter >=24 && death_counter <40)
        {
            moving_speed = moving_start_counter % 2;
            setY(y()+moving_speed);
        }
        else
        {
            moving_speed = 1;
            setY(y()+moving_speed);
        }
        death_counter += moving_speed;

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
            if(blocked_counter==0)
            {
            	//make the baby visible and stop big bertha
                baby->setZValue(3);
                baby->setScript_Move(true,dir);
                blocked_counter++;
            }
        	//increase blocked counter
            else if(blocked_counter>0 && blocked_counter<48)
                blocked_counter++;
        	//restart to moving big bertha
            else if(blocked_counter==48)
            {
                script_counter++;
                blocked_counter=0;
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
    if(!launch_baby)
    {
        baby->setZValue(1);
        baby->setPos(pos() + QPoint(5, 11));
    }
    else if(launch_baby && script_counter>=41)
    {
        baby->setZValue(1);
        baby->setPos(pos() + QPoint(5, 11));
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

    if(!baby->getScript_Move())
        baby->die();            
    else
        baby->setBaby_free(true);

}

//todo togliere
void BigBertha::state()
{

    //avro' due stati, uno in cui Big Bertha va solo annanzi, e uno in cui BigBertha lascia il pesce, va annanzi e se lo remagna
    //per adesso posso fare che se Mario salta, allora si setta lo script che sputa chello schifo

    
    ////per adesso uso una funzione random solo per provare
    //count_script++;
    //if(count_script % 2 == 0)
    //{
    //    launch_baby = true;
    //    blocked_counter = 0;
    //}
    //else
    //    launch_baby = false;
}
