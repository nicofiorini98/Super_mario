#include "BabyCheep.h"

#include "Sprites.h"
#include "Sounds.h"

BabyCheep::BabyCheep(QPoint position,Direction direction) : Enemy()
{
    // set attribute
    dir = direction;
    slow        = true;
    falling     = false;
    script_move = false;
    baby_free   =false;
    script_duration = 55;

    // animation divisor
    animation_div = 8 ;

    script_counter = 0 ;
    moving_start_counter = 0;

    // durations
    death_duration = 300;

    // textures
    texture_swim[0] = Sprites::instance()->get("baby-cheep-0");
    texture_swim[1] = Sprites::instance()->get("baby-cheep-1");
    texture_death   = Sprites::instance()->get("baby-cheep-0").transformed(QTransform().scale(1, -1));


    // set texture and correct y-coordinate w.r.t. texture height
    setPixmap(texture_swim[0]);
    setPos   (position);
    setZValue(3);

}

void BabyCheep::setScript_Move(bool _script_move, Direction _dir)
{
    dir = _dir;
    script_counter       = 0;
    moving_start_counter = 0;
    script_move          = _script_move;
}

void BabyCheep::advance()
{
	//baby cheep is based with two fondamental movements
	//when script_move, baby is launched from big bertha
	//and when is inside of the mouth, and the position is the same of big bertha

	//dying when go out the scene
    if (pos().x() >= 150 * 16 || pos().x() <= 0)
    {
        dying = true;
    }
	
	//bounce and fall when dying
    if (dying)
    {
        if (death_counter >= 0 && death_counter <= 20)
            setY(y() - (animation_counter % 2));
        else
            setY(y() + 1);
        return;
    }

	//stop to move with the script when the script_duration is reached 
    if (script_move && script_counter >script_duration)
    {
        moving_start_counter =0;
        script_move = false;
    }

	//baby go away when the mother is death 
    if(baby_free)
    {
        script_move  = false;
        moving_speed = moving_start_counter%2;

        if(dir==RIGHT)
            setX(x()+moving_speed);
        else
            setX(x()-moving_speed);

        moving_start_counter++;

        return;
    }

    //manage the moving_speed when is launched from the big bertha's mouth
    if (script_move)
    {
        if(moving_start_counter>=0)
          moving_start_counter++;

        if (script_counter < 8 )
        {
            moving_speed=moving_start_counter % 3 ==0; //0.33 speed
            script_counter += moving_speed;
        }

        else if (script_counter >= 8 && script_counter < 16 )
        {
            moving_speed=moving_start_counter % 2;  //0.5 speed
            script_counter+=moving_speed;
        }
        else if(script_counter >= 16 && script_counter < 32)
        {
            moving_speed=1;
            script_counter+=moving_speed;
        }
        else if(script_counter >= 32 && script_counter<40)
        {
            moving_speed = moving_start_counter%2;  //0.5 speed
            script_counter += moving_speed;
        }
        else if(script_counter>=40 && script_counter<=48 )
        {
            moving_speed=moving_start_counter % 3 ==0; //0.33 speed
            script_counter+=moving_speed;
        }
        else
        {
            moving_speed = -(moving_start_counter%2);
            script_counter++;
        }


        if(dir==RIGHT)
            setX(x()+moving_speed);
        else
            setX(x()-moving_speed);


    }
    
}


void BabyCheep::animate()
{
    Entity::animate();

    // save current texture height (for later correction)  // non credo serve per baby cheep
    int prev_h = boundingRect().height();

    // set the proper texture
    if (dying)
        setPixmap(texture_death);
    else if (moving)
        setPixmap(texture_swim[(animation_counter / animation_div) % 2]);

    if (dir == RIGHT)
        setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
}

void BabyCheep::hit(Object* what, Direction fromDir)
{
    Object::hit(what, fromDir);
}

void BabyCheep::hurt()
{
    Sounds::instance()->play("stomp");
    if(script_move || baby_free)
        death_duration=100;
    else
        death_duration=1;
    dying = true;
	
    moving_start_counter =-1;
}

void BabyCheep::setBabyFree(bool _baby_free)
{
    moving_start_counter = 0;
    script_move = false;
    baby_free = _baby_free;
}
