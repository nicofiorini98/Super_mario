#pragma once

#include "Entity.h"
#include "Collectable.h"


class Mario : public Entity 
{
	
	protected:

		// textures
		QPixmap texture_stand[2];			// small/big stand texture
		QPixmap texture_walking[2][4];		// small/big walking animations
		QPixmap texture_super_running[2][3];//small/big super running animations
		QPixmap texture_jumping[2];			// small/big jumping texture
		QPixmap texture_falling[2];			// small/big falling texture
		QPixmap texture_brake[2];			// small/big brake texture
		QPixmap texture_crouch;				// big crouch texture
		QPixmap texture_small2big[12];		// transformation small-to-big
		QPixmap texture_small_swimming[4];	// smallswimming texture
		QPixmap texture_big_swimming[7];	// big swimming texture
		QPixmap texture_entering_pipe[2];	// small/big enetering into pipe texture 
		
		std::string item_taken;

		//mario fire texture
		QPixmap texture_fire_stand;
		QPixmap texture_fire_walking[4];
		QPixmap texture_fire_super_running[3];
		QPixmap texture_fire_jumping;		    // small/big jumping texture
		QPixmap texture_fire_falling;		    // small/big falling texture
		QPixmap texture_fire_brake;			    // small/big brake texture
		QPixmap texture_fire_crouch;		    //fire crouch texture
		QPixmap texture_fire_shoot[2];		    //fire attack texture
		QPixmap texture_fire_swimming[7];       //fire swimming texture
		QPixmap texture_fire_falling_inWater[4];//fire falling in water
		QPixmap texture_fire_entering_pipe;     //fire entering into pipe texture

		//mario raccoon texture
		QPixmap texture_raccoon_stand;          
		QPixmap texture_raccoon_walking[4];
		QPixmap texture_raccoon_super_running[3];
		QPixmap texture_raccoon_flying[3];
		QPixmap texture_raccoon_jumping;
		QPixmap texture_raccoon_falling[3];
		QPixmap texture_raccoon_brake;
		QPixmap texture_raccoon_crouch;
		QPixmap texture_raccoon_swimming[7];
	
		//todo vedere se manca raccoon falling in water
		QPixmap texture_raccoon_tail_attack[5]; //raccoon tail attck texture
		QPixmap texture_raccoon_entering_pipe;  //raccoon entering into pipe texture

		QPixmap texture_transformation[6];
	
		int animation_div;
		int script_move_speed;

	//flag da riunificare
		Direction prev_dir;
		bool super_running;
	
		bool small_swim;
		bool brake_swim;
	
		bool flying;
		bool fly_float;
		bool touch_pipe;
		bool fire;
		bool raccoon;
		bool attack;
		bool raccoon_attack;

		bool outOfWater;
		bool inWater;
		bool inWater_surface;                   // is in Water surface

	//counter da riunificare
		int fly_counter;
		int fly_start_counter;
		int fly_duration;
		int fly_speed;

		int falling_start_counter;

		
		
		int swim_counter;
		int swim_start_counter;
		int swim_rise_duration;
		int swim_fall_duration;

		int swim_speed;
		int dir_change_duration;
		int attack_counter;
	
	
		// flags
		bool running;						// is Mario running?
		bool big;							// is Mario big?
		bool crouch;						// is Mario crouched?
		bool swimming;                      // is Mario swimming?
		bool script_move_in_pipe;           // is Mario 
		bool entering_pipe;                 // is Mario entering the pipe?
		bool running_out_of_view;
		// counters
		int script_move_counter;
		int moving_start_counter;			// counts the number of frames since moving started
		int moving_stop_counter;			// counts the number of frames since moving stopped
		int dir_change_counter;				// counts the number of frames since direction changed
		int transformation_counter;			// counts the number of frames since transformation started
		
		//da riunificare
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
		bool isOnPipe(std::string level_name);
		bool isUnderPipe(std::string level_name);
		bool isEnteringPipe() { return entering_pipe; }
		Direction getDirection() { return dir;}
		std::string ItemTaken() const { return item_taken; }

		bool isInWater() { return inWater; }
		bool isRaccoonAttack() { return raccoon_attack; }
		bool isSuperRunning() { return super_running; }
	
		//bool isRaccoon() { return raccoon; } //todo credo conviene fare una funzione che restituisce in che stato è mario

		void setRunning(bool _running);
		void setScriptMove(bool _script_move) { script_move = _script_move; }
		
		void setAttack(bool _attack) { attack = _attack; } //vedere nome


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

		// crouch
		void setCrouch(bool active);

		void powerUp(spawnable_t _power);  //todo aggiungere spawnable_t
	
		void enterPipe(Direction fromDir);
};