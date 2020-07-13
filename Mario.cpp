#include "Mario.h"
#include "Game.h"
#include "Sprites.h"
#include "Sounds.h"
#include "Enemy.h"
#include "Iceberg.h"
#include "Pipe.h"
#include "Muncher.h"
#include "GoalRoulette.h"
#include <iostream>
#include "ScoreSpawnable.h"
#include "KoopaTroopa.h"
#include "FireBall.h"
#include "Splash.h"
#include "BrickBlock.h"

Mario::Mario(QPoint position,std::string _level_name) : Entity()
{
	power = 0;			
	prev_power = -1;
	score = 0;
	lives = 0;

	bounce_block = false;
	rebound = false;
	injured = false;
		
	prev_dir = dir;
	// set flags
	level_name = _level_name; 
	moving = false;
	running = false;
	super_running = false;

	//flag for manage mario in the space
	outOfWater = true;
	inWater = false;
	inWater_surface = false;
	splash = false;
	
	big = false;
	fire = false;
	raccoon = false;
	crouch = false;
	script_move_in_pipe = false;
	entering_pipe = false;
	running_out_of_view = false;

	attack = false;
	raccoon_attack = false;

	//flag for InWater
	swimming = false;
	small_swim = false;
	brake_swim = false;


	//flag for mario raccoon fly
	flying = false;
	fly_float = false;

	//set swim counter
	swim_speed = 1;
	swim_counter = -1;
	swim_start_counter = -1;
	swim_rise_duration = 2 * 16;
	swim_fall_duration = 32;

	//set fly counter
	fly_counter = -1;
	fly_start_counter = -1;
	fly_duration = 48;
	fly_speed = 1;

	attack_counter = 0;
	// set counters
	script_move_counter = 0;
	script_move_speed = 1;
	moving_start_counter = -1;
	moving_stop_counter = -1;
	dir_change_counter = -1;
	dir_change_duration = 30;  
	transformation_counter = -1;
	injured_counter = 0;
	death_duration = 200; 
	//livel_ended_counter = 0;

	item_taken = "";

	// animation divisors
	animation_div = 1;

	// durations
	jumping_duration = 4 * 16;
	
	// textures
	texture_stand[0] = Sprites::instance()->get("mario-small-stand");
	texture_stand[1] = Sprites::instance()->get("mario-big-stand");
	texture_jumping[0] = Sprites::instance()->get("mario-small-jump");
	texture_jumping[1] = Sprites::instance()->get("mario-big-jump");
	texture_falling[0] = Sprites::instance()->get("mario-small-fall");
	texture_falling[1] = Sprites::instance()->get("mario-big-fall");
	texture_brake[0] = Sprites::instance()->get("mario-small-brake").transformed(QTransform().scale(-1, 1));
	texture_brake[1] = Sprites::instance()->get("mario-big-brake").transformed(QTransform().scale(-1, 1));

	texture_crouch = Sprites::instance()->get("mario-big-crouch");

	texture_walking[0][0] = Sprites::instance()->get("mario-small-walk-0");
	texture_walking[0][1] = Sprites::instance()->get("mario-small-walk-1");
	texture_walking[0][2] = Sprites::instance()->get("mario-small-walk-2");
	texture_walking[0][3] = Sprites::instance()->get("mario-small-walk-3");
	texture_walking[1][0] = Sprites::instance()->get("mario-big-walk-0");
	texture_walking[1][1] = Sprites::instance()->get("mario-big-walk-1");
	texture_walking[1][2] = Sprites::instance()->get("mario-big-walk-2");
	texture_walking[1][3] = Sprites::instance()->get("mario-big-walk-3");

	//texture in super_running mode
	texture_super_running[0][0] = Sprites::instance()->get("mario-small-run-0");
	texture_super_running[0][1] = Sprites::instance()->get("mario-small-run-1");
	texture_super_running[0][2] = Sprites::instance()->get("mario-small-run-2");
	texture_super_running[1][0] = Sprites::instance()->get("mario-big-run-0");
	texture_super_running[1][1] = Sprites::instance()->get("mario-big-run-1");
	texture_super_running[1][2] = Sprites::instance()->get("mario-big-run-2");
	texture_super_jumping[0]    = Sprites::instance()->get("mario-small-super-jump");
	texture_super_jumping[1]    = Sprites::instance()->get("mario-big-super-jump");
	texture_fire_super_jumping  = Sprites::instance()->get("mario-fire-super-jump");


	//texture transformation small2big
	texture_small2big[0] = Sprites::instance()->get("mario-half");
	texture_small2big[1] = texture_stand[0];
	texture_small2big[2] = Sprites::instance()->get("mario-half");
	texture_small2big[3] = texture_stand[0];
	texture_small2big[4] = Sprites::instance()->get("mario-half");
	texture_small2big[5] = texture_stand[0];
	texture_small2big[6] = Sprites::instance()->get("mario-half");
	texture_small2big[7] = texture_stand[1];
	texture_small2big[8] = Sprites::instance()->get("mario-half");
	texture_small2big[9] = texture_stand[1];
	texture_small2big[10] = Sprites::instance()->get("mario-half");
	texture_small2big[11] = texture_stand[1];
	texture_dying= Sprites::instance()->get("mario-small-dying");
	texture_transparent[0]= Sprites::instance()->get("transparent1");
	texture_transparent[1]= Sprites::instance()->get("transparent2");

	//texture transformation fire and raccoon
	texture_transformation[0] = Sprites::instance()->get("mario-transformation-0");
	texture_transformation[1] = Sprites::instance()->get("mario-transformation-1");
	texture_transformation[2] = Sprites::instance()->get("mario-transformation-2");
	texture_transformation[3] = Sprites::instance()->get("mario-transformation-3");
	texture_transformation[4] = Sprites::instance()->get("mario-transformation-4");
	texture_transformation[5] = Sprites::instance()->get("mario-transformation-5");

	//mario small texture InWater
	texture_small_swimming[0] = Sprites::instance()->get("mario-small-swim-0");
	texture_small_swimming[1] = Sprites::instance()->get("mario-small-swim-1");
	texture_small_swimming[2] = Sprites::instance()->get("mario-small-swim-2");
	texture_small_swimming[3] = Sprites::instance()->get("mario-small-swim-3");

	//mario big texture InWater
	texture_big_swimming[0] = Sprites::instance()->get("mario-big-swim-0");
	texture_big_swimming[1] = Sprites::instance()->get("mario-big-swim-1");
	texture_big_swimming[2] = Sprites::instance()->get("mario-big-swim-2");
	texture_big_swimming[3] = Sprites::instance()->get("mario-big-swim-3");
	texture_big_swimming[4] = Sprites::instance()->get("mario-big-swim-4");
	texture_big_swimming[5] = Sprites::instance()->get("mario-big-swim-5");
	texture_big_swimming[6] = Sprites::instance()->get("mario-big-swim-6");

	//mario fire texture OutOfWater
	texture_fire_stand = Sprites::instance()->get("mario-fire-stand");
	texture_fire_jumping = Sprites::instance()->get("mario-fire-jump");
	texture_fire_falling = Sprites::instance()->get("mario-fire-fall");
	texture_fire_brake = Sprites::instance()->get("mario-fire-brake").transformed(QTransform().scale(-1, 1));
	texture_fire_crouch = Sprites::instance()->get("mario-fire-crouch");
	texture_fire_walking[0] = Sprites::instance()->get("mario-fire-walk-0");
	texture_fire_walking[1] = Sprites::instance()->get("mario-fire-walk-1");
	texture_fire_walking[2] = Sprites::instance()->get("mario-fire-walk-2");
	texture_fire_walking[3] = Sprites::instance()->get("mario-fire-walk-3");

	//texture fire run
	texture_fire_super_running[0] = Sprites::instance()->get("mario-fire-run-0");
	texture_fire_super_running[1] = Sprites::instance()->get("mario-fire-run-1");
	texture_fire_super_running[2] = Sprites::instance()->get("mario-fire-run-2");

	//texture mario
	texture_fire_shoot[0] = Sprites::instance()->get("mario-fire-shoot-0");
	texture_fire_shoot[1] = Sprites::instance()->get("mario-fire-shoot-1");
	texture_fire_entering_pipe = Sprites::instance()->get("mario-fire-pipe");

	//mario fire texture inWater
	texture_fire_swimming[0] = Sprites::instance()->get("mario-fire-swim-0");
	texture_fire_swimming[1] = Sprites::instance()->get("mario-fire-swim-1");
	texture_fire_swimming[2] = Sprites::instance()->get("mario-fire-swim-2");
	texture_fire_swimming[3] = Sprites::instance()->get("mario-fire-swim-3");
	texture_fire_swimming[4] = Sprites::instance()->get("mario-fire-swim-4");
	texture_fire_swimming[5] = Sprites::instance()->get("mario-fire-swim-5");
	texture_fire_swimming[6] = Sprites::instance()->get("mario-fire-swim-6");

	//mario raccoon texture outOfWater
	texture_raccoon_stand = Sprites::instance()->get("mario-raccoon-stand");

	texture_raccoon_jumping = Sprites::instance()->get("mario-raccoon-jump");
	texture_raccoon_walking[0] = Sprites::instance()->get("mario-raccoon-walk-0");
	texture_raccoon_walking[1] = Sprites::instance()->get("mario-raccoon-walk-1");
	texture_raccoon_walking[2] = Sprites::instance()->get("mario-raccoon-walk-2");
	texture_raccoon_walking[3] = Sprites::instance()->get("mario-raccoon-walk-3");

	//texture raccoon sueper running
	texture_raccoon_super_running[0] = Sprites::instance()->get("mario-raccoon-run-0");
	texture_raccoon_super_running[1] = Sprites::instance()->get("mario-raccoon-run-1");
	texture_raccoon_super_running[2] = Sprites::instance()->get("mario-raccoon-run-2");

	//texture raccoon flying
	texture_raccoon_flying[0] = Sprites::instance()->get("mario-raccoon-fly-0");
	texture_raccoon_flying[1] = Sprites::instance()->get("mario-raccoon-fly-1");
	texture_raccoon_flying[2] = Sprites::instance()->get("mario-raccoon-fly-2");

	texture_raccoon_falling[0] = Sprites::instance()->get("mario-raccoon-fall-0");
	texture_raccoon_falling[1] = Sprites::instance()->get("mario-raccoon-fall-1");
	texture_raccoon_falling[2] = Sprites::instance()->get("mario-raccoon-fall-2");
	texture_raccoon_crouch = Sprites::instance()->get("mario-raccoon-crouch");
	texture_raccoon_brake = Sprites::instance()->get("mario-raccoon-brake");// .transformed(QTransform().scale(-1, 1));

	//mario raccoon tail attack texture
	texture_raccoon_tail_attack[0] = Sprites::instance()->get("mario-raccoon-tail-attack-0");
	texture_raccoon_tail_attack[1] = Sprites::instance()->get("mario-raccoon-tail-attack-1");
	texture_raccoon_tail_attack[2] = Sprites::instance()->get("mario-raccoon-tail-attack-2");// .transformed(QTransform().scale(-1, 1));
	texture_raccoon_tail_attack[3] = Sprites::instance()->get("mario-raccoon-tail-attack-3");
	texture_raccoon_tail_attack[4] = Sprites::instance()->get("mario-raccoon-tail-attack-4");
	
	//mario raccon texture InWater
	texture_raccoon_swimming[0] = Sprites::instance()->get("mario-raccoon-swim-0");
	texture_raccoon_swimming[1] = Sprites::instance()->get("mario-raccoon-swim-1");
	texture_raccoon_swimming[2] = Sprites::instance()->get("mario-raccoon-swim-2");
	texture_raccoon_swimming[3] = Sprites::instance()->get("mario-raccoon-swim-3");
	texture_raccoon_swimming[4] = Sprites::instance()->get("mario-raccoon-swim-4");
	texture_raccoon_swimming[5] = Sprites::instance()->get("mario-raccoon-swim-5");
	texture_raccoon_swimming[6] = Sprites::instance()->get("mario-raccoon-swim-6");

	//sono le texture per l'animazione della pipe
	texture_entering_pipe[0] = Sprites::instance()->get("mario-small-pipe");
	texture_entering_pipe[1] = Sprites::instance()->get("mario-big-pipe");
	texture_raccoon_entering_pipe = Sprites::instance()->get("mario-raccoon-tail-attack-1");

	
	// set texture and correct y-coordinate w.r.t. texture height
	setPixmap(texture_stand[big]);
	setPos(position - QPoint(0, pixmap().height()));

	// Mario is at a higher layer than other objects
	setZValue(6);
}

void Mario::advance()
{
	//std::cout << "walkable_object : " << walkable_object << '\n';
	if (prev_power != power)
		Hud::instance()->updatePanel("PowerMeter", std::to_string(power));
	//std::cout << "collidable:" << collidable << "\n";
	
	if (dying)
	{
		moving = false;
		collidable = false;
		falling = false;
		
		if (death_counter < death_duration / 3)
			setY(y() - 2);
		else
			setY(y() + 2);
		Entity::advance();
		return;
	}

	splash = false;
	//check position of mario for manage the physic parameters in the space
	if(level_name=="World 6-9-2" && outOfWater && !jumping && falling && pos().y() >= 16*16 )
	{
		//do splash when go inWater from the water surface
		if (pos().y() <= 16 * 16 + 4)
			splash = true;
		
		falling_start_counter = 0;
		falling_counter = 0;
		inWater = true;
		outOfWater = false;
		if (moving)
			moving_start_counter = 0;
		else
			moving_speed = 0;
	}
	else if(level_name == "World 6-9-2" && script_move && inWater && pos().y()<=16*16-8)
	{
		inWater = false;
		outOfWater = true;
		if (moving)
			moving_start_counter = 0;
		
	}
	else if(level_name == "World 6-9-2" && script_move && outOfWater && pos().y()>16*16-8)
	{
		inWater = true;
		outOfWater = false;
		if (moving)
			moving_start_counter = 0;
	}	else if(level_name=="World 6-9-3")
	{
		outOfWater = true;
		inWater = false;
	}
	if(splash)
		new Splash(pos());
	
	if (running_out_of_view)
	{
		moving_speed = ((animation_counter / 2) % 2) + 1;
		if (pos().x() >= 96*16)
			moving = false;
	}
	if (raccoon)
	{
		//manage asymmetry texture of mario raccoon
		if (prev_dir != dir /*&& (outOfWater || walkable_object)*/ && !script_move_in_pipe)
		{
			//todo togliere stampa
			//std::cout << "asymmetry correction\n";
			setX(x() + (dir == LEFT ? 8 : -8));
			
			prev_dir = dir;
			solveCollisions();
		}
	}
	if (script_move_in_pipe)
	{
		if ((!big && ((dir == DOWN && script_move_counter == 97) || (dir == UP && script_move_counter == 128)))
			|| (big && ((dir == DOWN && script_move_counter == 128) || (dir == UP && script_move_counter == 180))))
		{
			exitPipe();
			//todo , remove this, is for debug
			//if (level_name == "World 6-9-2")
				//setPos(38 * 16, 23 * 16);
			//	setPos(106 * 16, 9 * 16);
		}

		if (script_move_counter >= 0)
			script_move_counter++;

		script_move_speed = script_move_counter % 2 == 1;    // speed 0.5

		if (dir == DOWN)
			setY(y() + script_move_speed);
		else if (dir == UP)
			setY(y() - script_move_speed);
		
		if (!big)
		{
			if (script_move_counter == 32)
				Game::instance()->changeLevel(dir);
		}
		else
		{
			if (script_move_counter == 64)
				Game::instance()->changeLevel(dir);
		}		
	}
	// slow down jumping speed during last iterations
	if (bounce_block)
	{
		falling = false;
		if (rebound)
			jumping_duration = 4 * 16 + 24;
		else if (!rebound)
			jumping_duration = 25 + 24;

		if (jump_counter < 12)
			jumping_speed = -1;
		else if (jump_counter >= 12 && jump_counter < 24)
			jumping_speed = 1;

		else if (jump_counter >= 24)
			jumping_speed = 3;
	}
	if(swimming)
	{
		prevPos = pos();
 
		swim_start_counter++;
		//swimming is composed of two part, swim rising and swim falling
		
		//swim rising
		if(swim_counter < swim_rise_duration)
		{
			if (!small_swim && !brake_swim)
			{
				if (swim_counter < swim_rise_duration / 8)//speed 1
					swim_speed = 1;

				else if (swim_counter >= swim_rise_duration / 8 && swim_counter < swim_rise_duration / 4)
					swim_speed = swim_start_counter % 2 + 1;

				else if (swim_counter >= swim_rise_duration / 4 && swim_counter < (swim_rise_duration / 4) + (swim_rise_duration / 8))
					swim_speed = 1;


				//fase di arrivo della nuotata in alto
				else if ((swim_counter >= swim_rise_duration - (swim_rise_duration / 8)))
					swim_speed = swim_start_counter % 2;

				setY(y() - swim_speed);
			}
			else if (small_swim && !brake_swim)
			{
				if (swim_counter < swim_rise_duration / 8)
					swim_speed = swim_start_counter % 2; //0.5 speed

				else if (swim_counter >= swim_rise_duration / 8 && swim_counter < swim_rise_duration / 4)
					swim_speed = 1;

				else if ((swim_counter >= swim_rise_duration - (swim_rise_duration / 8)))
					swim_speed = swim_start_counter % 2;

				setY(y() - swim_speed);
			}
			else if (brake_swim) 
			{
				if (swim_counter < 2) 
				{
					swim_speed = 0;
					swim_counter++; 
				}
				else if (swim_counter >= 2 && swim_counter < swim_rise_duration)  
				{
					if (swim_start_counter % 4 == 0) // 0.25 speed
						swim_speed = 1;
					else
						swim_speed = 0;
				}
				setY(y() + swim_speed);
			}
		}
		//swim falling
		else if (swim_counter >= swim_rise_duration && swim_counter < swim_rise_duration + (swim_fall_duration / 4))
		{
			swim_speed = swim_start_counter % 4 == 0; //0.25 speed
			setY(y() + swim_speed);
		}
		else if (swim_counter >= (swim_rise_duration + (swim_fall_duration / 4)) && swim_counter < (swim_rise_duration + (swim_fall_duration / 3)))
		{
			swim_speed = swim_start_counter % 3 == 0; //0.33 speed
			setY(y() + swim_speed);
		}
		else if (swim_counter >= swim_rise_duration + swim_fall_duration / 3 && swim_counter < swim_rise_duration + swim_fall_duration)
		{
			swim_speed = swim_start_counter % 2;  //0.5 speed
			setY(y() + swim_speed);
		}
		else if (swim_counter >= swim_rise_duration + swim_fall_duration) //finally stop swimming
			endSwimming();

		swim_counter += swim_speed;  

		Entity::solveCollisions();
	}

	if(flying)
	{
		fly_start_counter++;

		//flying up
		if(fly_counter>= 0 && fly_counter<=fly_duration)
		{
			fly_speed = 2;
			setY(y() - fly_speed);
		}
		//flying down
		else if(fly_counter>fly_duration)
		{
			if (fly_counter <= fly_duration + 16)
			{
				falling_speed = 1;
				falling = true;
			}
			else
				falling_speed = 2;

			setY(y() + falling_speed);
		}
		fly_counter += fly_speed;

		moving_speed = 2;

		//todo, vedere se si può evitare, è il cambio di direzione di mario raccoon in volo
		if (dir_change_counter >= 0 && !walkable_object)
		{
			prev_dir = dir;
			Entity::setDirection(inverse(dir));
			dir_change_counter = -1;
		}

		//after 5", end of fly
		if (fly_start_counter > 333) // 333 frame finisce di vola, sono 5 secondi
			endFlying();

		solveCollisions();
	}
	if (fly_float)
	{
		prevPos = pos();
		
		fly_start_counter++; 
		 
		if (fly_counter < fly_duration)  // da migliorare
			fly_speed = fly_start_counter % 2 == 0;
		else
			endFlying();

		setY(y() + fly_speed);
		fly_counter += fly_speed;

		solveCollisions();
	}

	

	//advance standard out of the water
	if (outOfWater && !flying && !script_move && !running_out_of_view)
	{

		//todo  da ripensare questo pezzo
		if (moving)
		{
			// update moving acceleration / deceleration counters
			if (moving_stop_counter >= 0)  //bug prone for super running, check this part
				moving_stop_counter++;
			else if (moving_start_counter < 25)
				moving_start_counter++;
			else if (moving_start_counter >= 25 && running)
				moving_start_counter++;
		}
		

		//update direction change counter
		if (dir_change_counter >= 0 && !walkable_object) //change direction instantly in the air
		{
			prev_dir = dir;
			Entity::setDirection(inverse(dir));
			dir_change_counter = -1;
		}
		else if (dir_change_counter >= 0 && dir_change_counter < 20 && walkable_object)
		{
			//todo se non ho la freccia premuta, devo correre al contrario fino a quando non mi fermo
			dir_change_counter++;
		}
		else if (dir_change_counter >= 20 && walkable_object)
		{
			//reset counter 
			moving_start_counter = 0;

			//reset flag of super_running
			super_running = false;
			prev_dir = dir;
			Entity::setDirection(inverse(dir));
			dir_change_counter = -1;
		}

		if(!bounce_block)
		{
			if (jump_counter >= jumping_duration - 8)
				jumping_speed = 1 + (animation_counter % 2);

			else if (jump_counter >= jumping_duration - 16)
				jumping_speed = 2;
			else if (jump_counter >= jumping_duration - 24)
				jumping_speed = 2 + animation_counter % 2;
			else jumping_speed = 3;

		}

		// slow down falling speed during first iterations
		if (falling_counter < 8)
			falling_speed = 1;
		else if (falling_counter < 16)
			falling_speed = 2;
		else
			falling_speed = 3;
		
		//memorize power and then update
		prev_power = power;
		
		// horizontal acceleration when moving starts and moving stop is not active yet
		if (moving_start_counter >= 0 && moving_stop_counter < 0)
		{
			if (moving_start_counter <= 12)
			{
				moving_speed = moving_start_counter % 2;		// = 0.5 speed
				animation_div = 7;
			}
			else if (moving_start_counter > 12 && moving_start_counter <= 25)
			{
				moving_speed = moving_start_counter % 4 != 0;     //0.75 speed
				animation_div = 6;
			}
			else if (moving_start_counter > 25 && !running)
			{
				moving_speed = 1;                               //1 speed
				animation_div = 5;
			}
			else if (moving_start_counter > 25 && moving_start_counter <= 40 && running)
			{
				power = 1;
				moving_speed = (moving_start_counter % 4 == 0) + 1;	// 1.25 speed
				animation_div = 4;
			}
			else if (moving_start_counter > 40 && moving_start_counter <= 55 && running)
			{
				power = 2;
				moving_speed = moving_start_counter % 2 + 1;        //1.5 speed                              
				animation_div = 3;
			}
			else if (moving_start_counter > 55 && moving_start_counter <= 70 && running)
			{
				power = 3;
				moving_speed = (moving_start_counter % 4 != 0) + 1;  //1.75 speed
				animation_div = 3;
			}
			else if (moving_start_counter > 70 && moving_start_counter <= 85 && running)
			{
				power = 4;
				moving_speed = 2;	                                // 2 speed
				animation_div = 3;
			}
			else if (moving_start_counter > 85 && moving_start_counter <= 110 && running)
			{
				power = 5;
				moving_speed = moving_start_counter % 2 + 2;        //2.5 speed
				animation_div = 3;
			}
			else if (moving_start_counter > 110 && moving_start_counter <= 130 && running)
			{
				power = 6;
				moving_speed = 3;                                   // 3 speed
				animation_div = 2;
			}			
			else if (moving_start_counter > 130 && running)
			{
				power = 7;
				moving_speed = 4;                                    //4 speed
				super_running = true; 
				animation_div = 1;
			}
		}
	}
	//manage phisyc parameters for moving inWater
	if (inWater && !script_move) {

		//power meter is disabled in water
		prev_power = power;
		power = 0;
		
		// update moving acceleration / deceleration counters
		if (moving_stop_counter >= 0 && !walkable_object)
			moving_stop_counter++;
		else if (moving_stop_counter < 0 && !walkable_object)
			moving_start_counter++;

		// update direction change counter
		if (dir_change_counter >= 0 && walkable_object) //se ho il walkable object in acqua devo cambiare direzione istantaneamente
		{
			Entity::setDirection(inverse(dir));
			dir_change_counter = -1;
		}
		else if (dir_change_counter >= 0 && dir_change_counter < 20)
			dir_change_counter++;

		else if (dir_change_counter >= 20)
		{
			Entity::setDirection(inverse(dir));
			dir_change_counter = -1;
		}

		//constant speed for the walking in backdrop
		if (walkable_object)
		{
			moving_start_counter = 0;
			moving_speed = animation_counter % 2;
		}
		// horizontal acceleration in water, when mario isn't walking in the backdrop

		if (moving_start_counter >= 0 && moving_stop_counter < 0 && !walkable_object)
		{
			if (moving_start_counter <= 12)												//  0.5 speed
			{
				moving_speed = moving_start_counter % 2;
				animation_div = 12;
			}
			else if (moving_start_counter > 12 && moving_start_counter <= 25)			//0.75 speed
			{
				moving_speed = moving_start_counter % 4 != 0;
				animation_div = 10;
			}
			else if (moving_start_counter > 25 && moving_start_counter <= 50)			//1 speed
			{
				moving_speed = 1;
				animation_div = 8;
			}
			else if (moving_start_counter > 50)											//2   speed									
			{
				moving_speed = 1 + moving_start_counter % 2;
				animation_div = 6;
			}
		}

		if (falling_start_counter >= 0)  // incremento il falling_start_counter in entity ho messo che falling_counter+=falling_speed
			falling_start_counter++;

		//l'accellerazione iniziale fa parte della nuotata

		if (falling_counter <= 6)
			falling_speed = animation_counter % 2;
		else
			falling_speed = 1;

	}
	

	//horizontal deceleration when moving ends
	if (!script_move && moving_start_counter >= 0 && moving_stop_counter >= 0 && !running_out_of_view)
	{
		// decelerate for the same extent of the initial acceleration (max 30 frames)
		if (moving_stop_counter < std::min(moving_start_counter, 30))
		{
			moving_speed = moving_stop_counter % 2;		// = 0.5 speed
			animation_div = 7;
			moving = true;
		}
		// finally stop
		else
		{
			power = 0;
			moving = false;
			moving_start_counter = -1;
			moving_stop_counter = -1;
		}
	}

	//manage movement on the uphill and downhill
	if (script_move)
	{
		////change direction instantly
		if(dir_change_counter>0)
		{
			//prev_dir = dir; //todo check this
			
			setDirection(inverse(dir));
		}
		
		//stop moving instantly
		if (moving_stop_counter > 0) //todo, non mi fido di questo pezzo
		{
			//std::cout << "stop_moving_instantly\n";
			moving_stop_counter = -1;
			moving = false;
			
		}
		//physic paramether
		if (inWater)
		{
			moving_speed = animation_counter%2;

			if (swimming)
				script_move = false;
		}
		else if (outOfWater)
		{
			moving_speed = 1;

			if (jumping)
				script_move = false;
		}
	}
	
	Entity::advance();
}

// Mario jumps
void Mario::jump()
{
	if (!swimming)
	{
		// do nothing if already jumping
		if (jumping)
			return;

		//do fly float if raccoon and falling
		if (raccoon && (falling || fly_float))
		{
			startFlyFloating();
			return;
		}
		
		// start a jump
		jumping_speed = 3;				// reset jumping speed (modified in advance())
		jumping_duration = 4 * 16 + 5;  
		startJumping();

		// if jumping has started, play jump sound
		if (jumping)
			Sounds::instance()->play("jump");
	}
}

void Mario::swim()
{
	/*swim is based on three type of swimming
	 1)small swim
	 2)brake swim
	 3)swim standard (not small swim and not brake swim)
	*/
	
	//is mario in water surface?
	inWater_surface = pos().y() < (16 * 16) + 10;

	//when mario is on the walkable object, he takes a standard swim
	if (walkable_object)
	{
		small_swim = false;
		brake_swim = false;
		startSwimming();

		Sounds::instance()->play("jump"); // todo mettere suono swim
		return;
	}

	//when already swimming ..... //todo finire di commentare
	if(swimming)
	{
		if(inWater_surface)
		{
			if(Game::instance()->isKeyUpPressed()) // jump out of the water
			{
				endSwimming();
				outOfWater = true;
				inWater = false;
				falling = false;
				jump();
				new Splash(pos());
				return;
			}
			else
			{
				if (swim_counter >= swim_rise_duration + 4) //swim only start falling after a bit of time  //todo commento de merda
				{
					brake_swim = false;
					small_swim = false;
				}
				else
					return;
			}
		}

		//if mario swim when slow down the swimming, mario can start small swim
		if(brake_swim) 
		{
			brake_swim = false;
			small_swim = true;
		}
		//if mario swim when doing small swim, begin swim standard
		else if (small_swim) 
		{
			brake_swim = false;
			small_swim = false;
		}
		else if (!small_swim && !brake_swim && swim_counter >= swim_rise_duration + swim_fall_duration / 2)
			small_swim = true;
	}
	else  
	{
		if (!inWater_surface)  
			brake_swim = true;
		else
			small_swim = true;
	}
	startSwimming();

	if (swimming)
		Sounds::instance()->play("jump"); //todo mettere suono swim
}

void Mario::startJumping()
{
	crouch = false;
	Entity::startJumping();
}

void Mario::endJumping()
{
	
	jumping_duration = 4 * 16;
    bounce_block = false;
    Entity::endJumping();
}

void Mario::startSwimming()
{
	if (falling)
	{
		falling_start_counter = -1;
		falling = false;
	}

	swimming = true;
	swim_counter = 0;
	swim_start_counter = 0;
	walkable_object = nullptr;

	//set swim_duration 
	if (!small_swim && !brake_swim)
	{
		if (pos().y() - (16 * 16 - 5) > 32)
			swim_rise_duration = 32;
		else if (pos().y() - (16 * 16 - 5) > 4)
			swim_rise_duration = pos().y() - (16 * 16 - 10);
		else
			swim_rise_duration = 4;
	}
	else
		swim_rise_duration = 16;
}

void Mario::endSwimming()
{
	//reset flag and counter
	swimming = false;
	swim_counter = -1;
	swim_start_counter = -1;

	//start falling
	falling = true;
	falling_start_counter = 0;

	//reset flag of swim type
	small_swim = false;
	brake_swim = false;
}


void Mario::fly()
{
	fly_speed = 2;

	startFlying();

	// if jumping has started, play jump sound
	if (flying)
		Sounds::instance()->play("jump");//todo mettere suono del volo
}

void Mario::startFlying()
{
	if (!flying)
		fly_counter = 0;
		//fly_start_counter = 0;
	walkable_object = nullptr;
	flying = true;
	fly_counter = 0;
	falling = false;
	fly_duration = 64;

}

void Mario::endFlying()
{
	falling = true;
	flying = false;
	super_running = false;  //todo gestire bene questo super_running
	moving_start_counter = 0; //todo gestire bene
	fly_counter = -1;
	fly_start_counter = -1;
	
}

void Mario::startFlyFloating()
{
	fly_float = true;
	fly_counter = 0;
	fly_start_counter = 0;
	falling = false;
	fly_duration = 12;
}

void Mario::endFlyFloating()
{
	falling = true;
	fly_float = false;
	fly_counter = -1;
	fly_start_counter = -1;
}

// bounce
void Mario::bounce()
{
	// start a small jump
	jumping_duration = 1.5 * 16;
	falling = false;
	startJumping();
}

void Mario::bounceBlock()
{
	jumping_duration = 16 + 24;
	bounce_block = true;
	falling_counter = 0;

	jumping = true;

}

// @override setMoving() to add horizontal acceleration
void Mario::setMoving(bool _moving)
{
	//when _moving true, and crouch, don't move
	if (crouch && _moving)
		crouch = false;
		
	
	// transition move -> stop, then activate moving stop counter
	if (_moving == false && moving)
		if (!script_move)
			moving_stop_counter = 0;
		else
			moving = false;
	// transition stop -> move, then activate moving start counter
	else if (_moving == true && !moving)
		moving_start_counter = 0;

	Entity::setMoving(_moving);

}

// @override setDirection() to avoid instant direction change
void Mario::setDirection(Direction _dir)
{
	//don't change direction when the pipe travel is started
	if (script_move_in_pipe)
		return;
	
	//change direction instantly in script_move
	if(script_move)
	{
		
		prev_dir = dir;
		dir = _dir;
		dir_change_counter = -1;
	}
	
	else if (_dir != dir && moving)
	{
		// reset acceleration/deceleration counters
		moving_start_counter = 0;
		moving_stop_counter = -1;
		
		//start the direction counter
		dir_change_counter = 0;
	}
	else if (_dir != dir && !moving)
	{
		if (raccoon)
			prev_dir = dir;

		Entity::setDirection(_dir);
	}
}

void Mario::animate()
{
	Entity::animate();
	// save current texture height (for later correction)
	int prev_h = boundingRect().height();

	if (dying)
	{
		setPixmap(texture_dying);
		return;
	}
	if (script_move_in_pipe)
	{
		if (big && !fire && !raccoon)
			setPixmap(texture_entering_pipe[1]);
		else if (fire)
			setPixmap(texture_fire_entering_pipe); 
		else if (raccoon)
			setPixmap(texture_raccoon_entering_pipe);
		else
			setPixmap(texture_entering_pipe[0]);
	}
	//flashing texture when mario is injured
	else if (injured && transformation_counter < 0 && animation_counter % 6==0)
	{
		injured_counter++;
		
		if (big)
			setPixmap(texture_transparent[1]);
		else
			setPixmap(texture_transparent[0]);
		
		if (injured_counter >= 30)
		{
			injured_counter = 0;
			injured = false;
		}
	}
	//texture powerUp and powerDown
	else if(transformation_counter>=0)
	{
		transformation_counter++;
		if(!injured)
		{ 
			if (raccoon || fire || inWater)
				setPixmap(texture_transformation[(transformation_counter / 5) % 6]);
			else
				setPixmap(texture_small2big[(transformation_counter / 5) % 12]);
			
			if (transformation_counter >= 12 * 5)
			{
				if (raccoon && dir == RIGHT) //correction asymmetry of raccoon transformation
					setX(x() - 8);
				transformation_counter = -1;
				Game::instance()->setFreezed(false);
			}
		}
		else
		{
			if (big || inWater)
				setPixmap(texture_transformation[(transformation_counter / 5) % 6]);
			else
				setPixmap(texture_small2big[(-(transformation_counter / 5) % 12)+11]); 


			if (transformation_counter >= 12 * 5)
			{
				transformation_counter = -1;
				Game::instance()->setFreezed(false);
			}
		}
	}
	else if(outOfWater) //animate out of the water
	{
		//animation of raccoon in fly float
		if (raccoon && fly_float)
			setPixmap(texture_raccoon_falling[(animation_counter / 6) % 3]);
		else if (flying && !fly_float)
			setPixmap(texture_raccoon_flying[(animation_counter / 6) % 3]);

		else if (big && crouch)
		{
			if (!raccoon && !fire)
				setPixmap(texture_crouch);
			else if (fire)
				setPixmap(texture_fire_crouch);
			else if (raccoon)
				setPixmap(texture_raccoon_crouch);
		}

		//all texture of jumping
		else if (jumping && !super_running)
		{
			if (!fire && !raccoon)
				setPixmap(texture_jumping[big]);
			else if (fire)
				setPixmap(texture_fire_jumping);
			else if (raccoon)
				setPixmap(texture_raccoon_jumping);
			else
				setPixmap(texture_jumping[1]);
		}
		else if (jumping && super_running)
		{
			if (!fire && !raccoon)
				setPixmap(texture_super_jumping[big]);
			else if (fire)
				setPixmap(texture_fire_super_jumping);
		}

		else if (falling && !super_running)
		{
			if (!fire && !raccoon)
				setPixmap(texture_falling[big]);
			else if (fire)
				setPixmap(texture_fire_falling);
			else if (raccoon)
				setPixmap(texture_raccoon_falling[0]);
		}
		else if (falling && super_running)
		{
			if (!fire && !raccoon)
				setPixmap(texture_super_jumping[big]);
			else if (fire)
				setPixmap(texture_fire_super_jumping);
		}
		else if (moving && !super_running)
		{
			if (!raccoon && !fire)
			{
				if (dir_change_counter > 0)
					setPixmap(texture_brake[big]);
				else
					setPixmap(texture_walking[big][(animation_counter / animation_div) % 4]);
			}
			else if (fire)
			{
				if (dir_change_counter > 0)
					setPixmap(texture_fire_brake);
				else
					setPixmap(texture_fire_walking[(animation_counter / animation_div) % 4]);
			}
			else if (raccoon)
			{
				if (dir_change_counter > 0)
					setPixmap(texture_raccoon_brake);
				else
					setPixmap(texture_raccoon_walking[(animation_counter / animation_div) % 4]);
			}
		}
		else if (moving && super_running)
		{
			if (!raccoon && !fire)
			{
				if (dir_change_counter > 0)
					setPixmap(texture_brake[big]);
				else
					setPixmap(texture_super_running[big][(animation_counter / animation_div) % 3]);
			}
			else if (fire)
			{
				if (dir_change_counter > 0)
					setPixmap(texture_fire_brake);
				else
					setPixmap(texture_fire_super_running[(animation_counter / animation_div) % 3]);
			}
			else if (raccoon)
			{
				if (dir_change_counter > 0)
					setPixmap(texture_raccoon_brake);
				else
					setPixmap(texture_raccoon_super_running[(animation_counter / animation_div) % 3]);
			}
		}
		else
		{
			if (!fire && !raccoon)
				setPixmap(texture_stand[big]);
			else if (fire)
				setPixmap(texture_fire_stand);
			else if (raccoon)
				setPixmap(texture_raccoon_stand);
		}
	}
	else if (inWater)
	{
		if (!walkable_object)
		{
			//swimming and fall inWater animation of mario small
			if (!big)
			{
				if (swimming)
					setPixmap(texture_small_swimming[(animation_counter / animation_div) % 4]);
				else if (falling)
					setPixmap(texture_small_swimming[(animation_counter / animation_div) % 2]);
			}

			//swimming and fall inWater animation of mario Big
			else if (big && !fire && !raccoon)
			{
				if (swimming)
					setPixmap(texture_big_swimming[((animation_counter / animation_div) % 3) + 4]);
				else if (falling)
					setPixmap(texture_big_swimming[(animation_counter / animation_div) % 4]);
			}
			else if (fire)
			{
				if (swimming)
					setPixmap(texture_fire_swimming[((animation_counter / animation_div) % 3) + 4]);
				else if (falling)
					setPixmap(texture_fire_swimming[(animation_counter / animation_div) % 4]);
			}
			else if (raccoon)
			{
				if (swimming)
					setPixmap(texture_raccoon_swimming[((animation_counter / animation_div) % 3) + 4]);
				else if (falling)
					setPixmap(texture_raccoon_swimming[(animation_counter / animation_div) % 4]);
			}
		}
		else
		{
			if (moving)
			{
				if (!fire && !raccoon)
					setPixmap(texture_walking[big][(animation_counter / animation_div) % 4]);
				else if (fire)
					setPixmap(texture_fire_walking[(animation_counter / animation_div) % 4]);
				else
					setPixmap(texture_raccoon_walking[(animation_counter / animation_div) % 4]);

			}
			else
			{
				if (!fire && !raccoon)
					setPixmap(texture_stand[big]);
				else if (fire)
					setPixmap(texture_fire_stand);
				else
					setPixmap(texture_raccoon_stand);
			}

		}

		//mirror texture istantly in the water   
		if (dir_change_counter > 0)
			setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
	}
	
	if (attack)
	{
		//attack with fire is shoot a fireBall
		if (fire)
		{
			attack_counter++;

			if (walkable_object)
				setPixmap(texture_fire_shoot[(attack_counter / 7) % 2]);
			else
				setPixmap(texture_fire_super_jumping);

			if (attack_counter > 7)
			{
				new FireBall(pos().toPoint() + QPoint(((dir == RIGHT) ? 6 : 0), 12), dir);
				Sounds::instance()->play("fireball");
				attack = false;
				attack_counter = 0;
			}
		}
		else if (raccoon && outOfWater)
		{
			attack_counter++;
			setPixmap(texture_raccoon_tail_attack[(attack_counter / 6) % 5]);

			if (attack_counter == 12)
			{

				raccoon_attack = true;
				prev_dir = dir;  //dir precedente
				dir = inverse(dir); //dir corrente
			}
			else if (attack_counter == 18)
			{
				Sounds::instance()->play("tail");
				raccoon_attack = false;
				prev_dir = dir;     //dir precedente
				dir = inverse(dir); //dir corrente
			}

			if (attack_counter > 30)
			{
				attack = false;
				attack_counter = 0;
			}

		}
	}
	//todo qua l'indentazione è sbagliata, vidi mpo

	// correct y position if texture height changed
	int cur_h = boundingRect().height();
	if (prev_h != cur_h)
		setY(y() - (cur_h - prev_h));

	// mirror the texture along the horizontal axis if needed
	if (dir == RIGHT)
		setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
}

// Mario has been hit
void Mario::hit(Object* what, Direction fromDir)
{
	Object::hit(what, fromDir);

	if (fromDir == DOWN && swimming && dynamic_cast<Inert*>(what))  // se sto nuotando e tocco verso il basso devo riprendere il walkable object
		walkable_object = dynamic_cast<Inert*>(what);

	
	if (swimming && (fromDir == DOWN || fromDir == UP))
		endSwimming();

	if (fly_float && (fromDir == DOWN))
		endFlyFloating();

	if (flying && (fromDir == DOWN))
		endFlying();

	if (dynamic_cast<Iceberg*>(what) && dynamic_cast<Iceberg*>(what)->type() == "downhill")
	{
		falling = false;
		falling_start_counter = -1;
		script_move = true;
		downhill = true;
	}
	else if (dynamic_cast<Iceberg*>(what) && dynamic_cast<Iceberg*>(what)->type() == "uphill")
	{
		falling = false;
		falling_start_counter = -1;
		script_move = true;
		downhill = false;
	}
	else
		script_move = false;


	if (dynamic_cast<GoalRoulette*>(what))
	{
		item_taken = dynamic_cast<GoalRoulette*>(what)->getContent();
		Game::instance()->endLevel();
		Game::instance()->stopGameTime();

		running_out_of_view = true;
		dir = RIGHT;
		moving = true;
	}
	
	/*if (dynamic_cast<BrickBlock*>(what) && fromDir == UNDETERMINED)
		solveCollisions();*/

	// disable deceleration if mario hits impenetrable object
	if (dynamic_cast<Inert*>(what) && (fromDir == LEFT || fromDir == RIGHT))
	{
		moving_start_counter = 0;
		if(script_move)  
			falling = true;
	}

	if (dynamic_cast<Enemy*>(what))
	{
		KoopaTroopa* koopa = dynamic_cast<KoopaTroopa*>(what);
		if (koopa)
		{
			if (fromDir == DOWN)
				bounce();
			else if(!koopa->isShell())
				powerDown();
		}
		else
			powerDown();
	}
}

// running = double moving speed
void Mario::setRunning(bool _running)
{
	
	// do nothing if running state does not change
	if (running == _running)
		return;

	// set new running state
	running = _running;
	if (!running)
	{
		super_running = false;
		moving_start_counter = 24;
	}
}

void Mario::enterPipe(Direction fromDir)
{
	if (raccoon && dir == RIGHT)
		setX(x() + 8);
	
	
	if (fromDir == DOWN)
	{
		jumping = false;
		jump_counter = 0;
		entering_pipe = true;
	}

	dir = inverse(fromDir);

	startPipeTravel();
	Sounds::instance()->play("pipe");
}

void Mario::exitPipe()
{
	endPipeTravel();
	if (dir == UP)
	{
		falling = true;
		prevPos = pos();
	}

	dir = RIGHT;
	setZValue(6);
	Sounds::instance()->play("pipe");
}


void Mario::startPipeTravel()
{
	entering_pipe = false;
	script_move_in_pipe = true;
	
	setZValue(1);

	collidable = false;

	Game::instance()->setFreezed(true);
}

void Mario::endPipeTravel()
{
	script_move_in_pipe = false;
	script_move_counter = 0;
	collidable = true;

	Game::instance()->setFreezed(false);
}

// override die method (Mario is a special case)
void Mario::die()
{
	// call superclass method
	dying = true;
	Game::instance()->gameover();

}

// crouch
void Mario::setCrouch(bool active)
{
	if (active && moving)
		setMoving(false);
	
	if (!jumping && !falling)
		crouch = active;

	if (!active)
		crouch = false;
}

void Mario::powerUp(spawnable_t _power) 
{
	if(_power == MUSHROOM)
		Sounds::instance()->play("eat");
	else if(_power== FLOWER)
		Sounds::instance()->play("eat");
	else if(_power== LEAF)
		Sounds::instance()->play("leaf");	

	transformation_counter = 0;

	//only for debug
	if(!_power) 
	{
		if (!big)
			big = true;
		else if (big && !fire && !raccoon)
			fire = true;
		else if (fire) 
		{
			fire = false;
			raccoon = true;
		}
		else
		{
			big = false;
			raccoon = false;
			fire = false;
		}
	}

	if (_power == MUSHROOM) //power up with mushroom
		big = true;
	
	else if (_power == FLOWER) //power up with flower
	{
		if (big)
		{
			raccoon = false;
			fire = true;
		}
		else
			big = true;
	}
	else if (_power == LEAF)
	{
		if (big)
		{
			fire = false;
			raccoon = true;
		}
		else
			big = true;
	}

	Game::instance()->setFreezed(true);
}


void Mario::powerDown()
{
	injured = true;
	transformation_counter = 0;

	if (raccoon)
	{
		raccoon = false;
	}
	else if (fire)
		fire = false;
	else if (big)
		big = false;
	else
		die();

	Sounds::instance()->play("leaf");
}


bool Mario::isOnPipe(std::string level_name)
{
	int pos_x = pos().x();
	if (raccoon && dir == RIGHT)
		pos_x += 8;
	/*
	if (((level_name == "World 6-9-1" && pos_x >= 14 * 16 + 4 && (pos_x + 16) <= 16 * 16 - 4)
		|| (level_name == "World 6-9-2" && pos_x >= 54 * 16 + 4 && (pos_x + 16) <= 56 * 16 - 4)) && !falling && !jumping)
		return true;
	else
		return false;*/
	if (!dynamic_cast<Pipe*>(walkable_object))
		return false;
	if (level_name == "World 6-9-1" && pos_x >= 14 * 16 + 4 && (pos_x + 16) <= 16 * 16 - 4)
		return true;
	else if (level_name == "World 6-9-2" && pos_x >= 54 * 16 + 4 && (pos_x + 16) <= 56 * 16 - 4 && !falling && !jumping /*&& pos().y() >= 22 * 16 - 2*/)
		return true;
	else
		return false;
	
}

bool Mario::isUnderPipe(std::string level_name)
{
	int pos_x = pos().x();
	if (raccoon && dir == RIGHT)
		pos_x += 8;
	
	if  ((level_name == "World 6-9-3" && pos_x >= 13*16 +4  && (pos_x + 16) <= 15*16 -4)
	   ||(level_name == "World 6-9-2" && pos_x >= 108*16  && (pos_x + 16) <= 110*16 ))  // rivedere questa riga
		return true;
	else 
		return false;
}

void Mario::updateScore(int score2add,QPoint pos)
{
	//update score 
	score += score2add;

	//spawn score animation
	if(score2add != 50 )
		new ScoreSpawnable(pos, std::to_string(score2add));

	//update score in the huds
	Hud::instance()->updatePanel("Score", std::to_string(score));
	
}

void Mario::updateLives(int lives2add, QPoint pos)
{
	lives += lives2add;
	
	new ScoreSpawnable(pos, "1up");
	Hud::instance()->updatePanel("LifeCounter", std::to_string(lives));
}

QPainterPath Mario::shape() const
{
	QPainterPath path;

	if(script_move_in_pipe)
	{
		path.addRect(3, boundingRect().top(), boundingRect().width() - 6, boundingRect().bottom() - 3);
		return path;
	}
	if (!big)
		path.addRect(3, boundingRect().top() + 3, boundingRect().width() - 6, boundingRect().bottom()-3);
	else if ((big && !raccoon) || transformation_counter>0)
		path.addRect(3, boundingRect().top() + 3, 10, boundingRect().bottom()-3);
	else if (raccoon)
	{
		if (attack && attack_counter == 12)
			path.addRect(dir == RIGHT ? 0 : 3, boundingRect().top() + 3, boundingRect().width() - 3, boundingRect().bottom() - 3);
		
		else
			path.addRect(dir==RIGHT ? 11:3, boundingRect().top() + 3, 10, boundingRect().bottom() - 3);
	}
	return path;
}
