#include "BabyCheep.h"

#include "Sprites.h"
#include "Sounds.h"

BabyCheep::BabyCheep(QPoint position,Direction direction) : Enemy()
{
    // set attribute
    pos_in = position;
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
    texture_swim[0] = Sprites::instance()->get("Baby-Cheep-0");
    texture_swim[1] = Sprites::instance()->get("Baby-Cheep-1");
    texture_death   = Sprites::instance()->get("Baby-Cheep-0").transformed(QTransform().scale(1, -1));


    // set texture and correct y-coordinate w.r.t. texture height
    setPixmap(texture_swim[0]);
    setPos   (position - QPoint(0, pixmap().height()));
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
    if (script_move && script_counter >script_duration)
    {
        moving_start_counter =0;
        script_move          = false;
    }


    //il movimento scriptato del pesce va avanti per 48 pixel e poi torna indietro per 7 pixel, sembra fedele all'originale

    //baby_free è per quando muore Big_Bertha e
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
    else
        return;
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

    //era dello goomba perch� da morto cambiava altezza
    // correct y position if texture height changed
    int cur_h = boundingRect().height();
    if (prev_h != cur_h)
        setY(y() - (cur_h - prev_h));

    if (dir == RIGHT)
        setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
}

void BabyCheep::hit(Object* what, Direction fromDir)
{
    Object::hit(what, fromDir);

    if ((dynamic_cast<Inert*>(what) /*|| dynamic_cast<Enemy*>(what)*/)
        && (fromDir == LEFT || fromDir == RIGHT))
        dir = inverse(dir);
}

void BabyCheep::hurt()
{
    Sounds::instance()->play("stomp");
    if(script_move || baby_free) // in questo modo ho una durata di morte istantanea se muore baby insieme alla mamma
        death_duration=100;
    else
        death_duration=1;
    dying = true;
    moving_start_counter =-1;
}

void BabyCheep::setBaby_free(bool _baby_free)
{
    moving_start_counter = 0; // potrei anche non metterlo
    script_move=false;
    baby_free = _baby_free;
}

//void Baby_Cheep::set_actual_pos() {
//	if (lim)
//		actual_pos = pos();
//}