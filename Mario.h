#pragma once

#include "Entity.h"
#include "Collectable.h"
#include "Hud.h"


class Mario : public Entity 
{
	
	protected:

		// textures
		QPixmap texture_stand[2];					//small/big stand texture
		QPixmap texture_walking[2][4];				//small/big walking animations
		QPixmap texture_super_running[2][3];		//small/big super running animations
		QPixmap texture_super_jumping[2];			//small/big super jumping texture
		QPixmap texture_jumping[2];					//small/big jumping texture
		QPixmap texture_falling[2];					//small/big falling texture
		QPixmap texture_brake[2];					// small/big brake texture
		QPixmap texture_crouch;						// big crouch texture
		QPixmap texture_small2big[12];				// transformation small-to-big
		QPixmap texture_small_swimming[4];			// smallswimming texture
		QPixmap texture_big_swimming[7];			// big swimming texture
		QPixmap texture_entering_pipe[2];			// small/big entering into pipe texture
		QPixmap texture_dying;						//dying texture
		QPixmap texture_transparent[2];				//injured texture
		
		QPixmap texture_fire_stand;					//fire stand texture
		QPixmap texture_fire_walking[4];			//fire walking texture
		QPixmap texture_fire_super_running[3];		//fire super runnin texture
		QPixmap texture_fire_super_jumping;			//fire super jumping texture
		QPixmap texture_fire_jumping;				//fire jumping texture
		QPixmap texture_fire_falling;				//fire falling texture
		QPixmap texture_fire_brake;					//fire brake texture
		QPixmap texture_fire_crouch;				//fire crouch texture
		QPixmap texture_fire_shoot[2];				//fire attack texture
		QPixmap texture_fire_swimming[7];			//fire swimming texture
		QPixmap texture_fire_falling_inWater[4];	//fire falling in water
		QPixmap texture_fire_entering_pipe;			//fire entering into pipe texture

		//mario raccoon texture
		QPixmap texture_raccoon_stand;				//raccoon stand texture
		QPixmap texture_raccoon_walking[4];			//raccoon walking texture
		QPixmap texture_raccoon_super_running[3];	//raccoon super running texture
		QPixmap texture_raccoon_flying[3];			//raccoon flying texture
		QPixmap texture_raccoon_jumping;			//raccoon jumping texture
		QPixmap texture_raccoon_falling[3];			//raccoon fallin texture
		QPixmap texture_raccoon_brake;				//raccoon brake texture
		QPixmap texture_raccoon_crouch;				//raccoon crouch texture
		QPixmap texture_raccoon_swimming[7];		//raccoon swimming texture
		QPixmap texture_raccoon_tail_attack[5];		//raccoon tail attck texture
		QPixmap texture_raccoon_entering_pipe;		//raccoon entering into pipe texture
		QPixmap texture_transformation[6];			//transformation texture
	
		std::string item_taken;						//card taken 

		int animation_div;							//animation divisor
		int script_move_speed;						//speed in pipe
		//flag da riunificare
		Direction prev_dir;							//previous frame direction
	
		bool super_running;							//is mario in super running?
		bool touch_pipe;							//is mario touch pipe?
		bool raccoon_attack;						//is mario raccoon attack?

		//flag for swim type
		bool small_swim;							
		bool brake_swim;

		//flag for fly in raccoon mode 
		bool flying;
		bool fly_float;

		//flag for raccoon mode 
		bool fire;
		bool raccoon;
		bool attack;
	
		
		//flag for manage physic parameters in the world
		bool outOfWater;
		bool inWater;
		bool inWater_surface;           

		//physic parameters for raccoon fly
		int fly_counter;
		int fly_start_counter;
		int fly_duration;
		int fly_speed;

		int falling_start_counter;

		//physic parameters for the swim
		int swim_counter;
		int swim_start_counter;
		int swim_rise_duration;
		int swim_fall_duration;
		int swim_speed;

		//physic parameters for directon change
		int dir_change_counter;				
		int dir_change_duration;			

		int attack_counter;
	
		// flags for manage the behaviour
		bool running;						// is Mario running?
		bool big;							// is Mario big?
		bool crouch;						// is Mario crouched?
		bool swimming;                      // is Mario swimming?
		bool splash;						// is Mario touching with water surface?
		bool script_move_in_pipe;           // is Mario moving into the pipe?
		bool entering_pipe;                 // is Mario entering the pipe?
		bool running_out_of_view;			// is Mario running out of view?
		bool bounce_block;					// is Mario bounce on the jump block?
		bool rebound;						// is Mario rebound on the jump block?
		bool injured;						// is Mario injured?
					

		//attribute for hud
		int power;							
		int prev_power;
		int score;
		int lives;
		
		int moving_start_counter;			// counts the number of frames since moving started
		int moving_stop_counter;			// counts the number of frames since moving stopped
	
		int transformation_counter;			// counts the number of frames since transformation started
		int injured_counter;				// counts the number of frames since flashing for injured started
		int script_move_counter;

		
		//override end jumping
		virtual void startJumping();
		virtual void endJumping();

		
		void startSwimming();
		void endSwimming();
		
		
		void startFlying();
		void endFlying();
	
		void startFlyFloating();
		void endFlyFloating();
	
		// utility functions
		void startPipeTravel();
		void endPipeTravel();
		void exitPipe();

	public:

		//@ovverride QPainter
		QPainterPath shape() const;

		Mario(QPoint position, std::string _level_name);


		// getters and setters
		bool isBig() { return big; }
		bool isRaccoon() { return raccoon; }
		bool isInjured() { return injured; }
		//bool isDying() { return dying; }
		bool isOnPipe(std::string level_name);
		bool isUnderPipe(std::string level_name);
		bool isEnteringPipe() { return entering_pipe; }
		bool isBouncing() { return bounce_block; }
		Direction getDirection() { return dir;}
		int getPower() { return power; }
		int getLives() { return lives; }
		int getScore() { return score; }

		//function for update attribute for hud
		void updateScore(int score2add,QPoint pos = QPoint(0,0));
		void updateLives(int lives2add,QPoint pos = QPoint(0, 0));
		std::string ItemTaken() const { return item_taken; }
		

		bool isInWater() { return inWater; }
		bool isRaccoonAttack() { return raccoon_attack; }
		bool isSuperRunning() { return super_running; }
		void setRebound(bool _rebound) { rebound = _rebound; }
		void setRunning(bool _running);
		void setScriptMove(bool _script_move) { script_move = _script_move;}
		void setFalling(bool _falling);
		
		void setAttack(bool _attack) { attack = _attack; } 


		// pure virtual methods that must be implemented
		virtual std::string name() { return "Mario"; }
		virtual void animate();
		virtual void hit(Object* what, Direction fromDir);

		// @override advance() for to add vertical/horizontal acceleration
		virtual void advance();

		// @override setMoving() to add horizontal acceleration
		virtual void setMoving(bool _moving);

		// @override setDirection() to avoid instant direction change
		virtual void setDirection(Direction _dir);

		// @override die method (Mario is a special case)
		virtual void die();

		// jump
		void jump();

		
		void swim();

		void fly();

		// bounce
		void bounce();

		void bounceBlock();

		// crouch
		void setCrouch(bool active);

		void powerUp(spawnable_t _power);  

		void powerDown();
	
		void enterPipe(Direction fromDir);
};