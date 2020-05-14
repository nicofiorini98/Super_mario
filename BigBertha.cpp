#include "BigBertha.h"
#include "Game.h"
#include <iostream>
#include "Sprites.h"
#include "Sounds.h"


BigBertha::BigBertha(QPoint position, Direction direction) : Enemy()
{
    //mario mi serve per la morte, siccome il salo sarà a sinistra, in base a dove si troverà mario
    mario = Game::instance()->getMario();
    script_counter  = 0;
    blocked_counter = 0;
    script_duration = 128;    //equivale alla lunghezza del raggio d'azione per adesso 128
    launch_baby = false;
    dir  = direction;
    slow = true;
    moving_start_counter = 0;


    // animation divisor
    animation_div = 8;

    // durations , da cambiare
    death_duration = 300;

    // textures
    texture_swim_close[0] = Sprites::instance()->get("Big-Bertha-3");
    texture_swim_close[1] = Sprites::instance()->get("Big-Bertha-2");
    texture_swim_open[0] = Sprites::instance()->get("Big-Bertha-1");
    texture_swim_open[1] = Sprites::instance()->get("Big-Bertha-0");
    texture_death = Sprites::instance()->get("Big-Bertha-0").transformed(QTransform().scale(1, -1));

    // non so se così va bene
    baby = new BabyCheep(position, dir);

    // set texture and correct y-coordinate w.r.t. texture height
    setPixmap(texture_swim_close[0]);
    setPos(position - QPoint(0, pixmap().height()));
    setZValue(2);

}

void BigBertha::advance()  //vedere un po' come devo pensare big Bertha
{

   // if(dying)

    if (script_counter > script_duration) //  se finisce lo script vedi in che stato sono e riazzera i counter
    {
        script_counter=0;
        moving_start_counter = 0;
        state();
    }

    if(moving_start_counter >= 0)
         moving_start_counter++;

    // utilizzo ancora lo script_counter sti cazzi, con uno script_duration che è uguale al death_duration che ho messo in hurt()
    if(dying)
    {
        //todo, il salto deve essere fatto anche lateralmente, dipende da dove mario colpisce big_bertha

        // è il salto e l'affogamento
        if(script_counter < 10)
        {
            moving_speed = moving_start_counter % 2;
            setY(y()-moving_speed);
        }
        else if(script_counter >=8 && script_counter<24) // ho messo che il salto prima de affoga è 16, forse è più lungo, 32 mi sembra eccessivo
        {
            moving_speed = 1;
            setY(y()-moving_speed);
        }
        else if(script_counter >=24 && script_counter<40)
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

        return; // serve per non entrare negli altri if, se sto morendo non devo fare nessun altro advance oltre a questo
    }

    if(!launch_baby)  // accellerazioni senza lancio dello figlio
    {
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

        else if (script_counter >= 104 && script_counter < 112) //0.5 speed
        {
            moving_speed = moving_start_counter % 2 == 0;
            script_counter += moving_speed;
        }
        else if (script_counter == 112)
        {
            dir = inverse(dir);
            script_counter++;
        }
        else
        {
            moving_speed = moving_start_counter % 2; // 0.5 speed
            script_counter += moving_speed;
        }

    }
    //sta lanciando
    else
    {
        if(script_counter==0)
        {
            moving_speed=0;
            if(blocked_counter==0)
            {
                baby->setZValue(3);
                baby->setScript_Move(true,dir);
                blocked_counter++;
            }
            else if(blocked_counter>0 && blocked_counter<48)
            {
               // std::cout<<"sto fermo\n";
                blocked_counter++;
            }
            else if(blocked_counter==48)
            {
                script_counter++;
                blocked_counter=0;  //mesa è fatto nello state()
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
             moving_speed = (moving_start_counter % 3 ==0) +1;
             script_counter += moving_speed;
         }

        else if (script_counter >= 96 && script_counter < 104)//0.75 speed
        {
            moving_speed = moving_start_counter % 4 !=0 ;
            script_counter += moving_speed;
        }

        else if (script_counter >= 104 && script_counter < 112) //0.5 speed
        {
            moving_speed = moving_start_counter % 2;
            script_counter += moving_speed;
        }
        else if (script_counter == 112)
        {
            dir = inverse(dir);
            script_counter++;
        }
        else
        {
            moving_speed = moving_start_counter % 3 == 0 ;
            script_counter+=moving_speed;
        }
    }
    //avanzamento del movimento scriptato

    if ( dir == RIGHT)
        setX(x() + moving_speed);
    else
        setX(x() - moving_speed);

    //if not launch baby
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


    if(moving_start_counter % 128 == 1 ) // non posso usare lo script_counter, questo perchè altrimenti se non incrementa,
        //mi incrementa il tutto più di una volta
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
        setPixmap(texture_swim_close[(animation_counter / animation_div) % 2]);
    else if(launch_baby && script_counter>=55)
        setPixmap(texture_swim_close[(animation_counter / animation_div) % 2]);
    else
        setPixmap(texture_swim_open[(animation_counter/animation_div)%2]);


    if (dir == RIGHT)
        setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
}

void BigBertha::hit(Object* what, Direction fromDir)
{
    Object::hit(what, fromDir);

    if ((dynamic_cast<Inert*>(what) || dynamic_cast<Enemy*>(what))
        && (fromDir == LEFT || fromDir == RIGHT))
        dir = inverse(dir);
}

void BigBertha::hurt()
{
    Sounds::instance()->play("stomp");
    dying = true;
    script_counter=0;
    moving_start_counter = 0;
    script_duration = death_duration; // faccio una sorta di movimento scriptato

    if(!baby->getScript_Move()) // se baby sta dentro la bocca, e big viene ferita allora baby deve morire istantaneamente
        baby->die();            // l'istantaneamente lo gestisco nel die() di baby_cheep
    else
        baby->setBaby_free(true);


    //devo far fermare big bertha, fargli fare un saltino e poi deve affogare
}

void BigBertha::state()
{

    //avro' due stati, uno in cui Big Bertha va solo annanzi, e uno in cui BigBertha lascia il pesce, va annanzi e se lo remagna
    //per adesso posso fare che se Mario salta, allora si setta lo script che sputa chello schifo


    //per adesso uso una funzione random solo per provare
    count_script++;
    if(count_script % 2 == 0)
    {
        launch_baby = true;
        blocked_counter = 0;
    }
    else
        launch_baby = false;
}
