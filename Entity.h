#pragma once

#include "Inert.h"


// Entity object are "living", i.e. they can move, animate, fall,
// jump, collide, die, etc.
class Entity : public Object
{
    protected:

		// physics parameters
		int moving_speed;					// moving speed (pixels/frame)
		int moving_speed_div;				// see 'slow' flag
		int jumping_speed;					// jumping speed (pixels/frame)
		int falling_speed;					// falling speed (pixels/frame)

		// flags
		Direction dir;						// the direction of movement
        bool moving;						// is moving?
        bool jumping;						// is jumping?
        bool falling;						// is falling (gravity)?
		bool dying;							// is dying
		bool dead;							// is dead?
		bool freezed;						// cannot temporarily move
		bool phantom;						// no collisions with other entities //todo vedere dove lo usa
		bool slow;						    // subpixel moving speed: move 1 pixel every moving_speed_div frames
		bool script_move;                   //script move for uphill and downhill
		bool downhill;
	
		// counters
		int animation_counter;				// main animation cycle
        int jump_counter;					// counts the number of frames since jump started
		int falling_counter;				// counts the number of frames since falling started
		int death_counter;					// counts the number of frames since the entity has been scheduled for death
		
		// durations (= limits for counters that are time-limited)
		int jumping_duration;				// jump duration (frames)
		int death_duration;					// limit for death_counter
		
        // others
		int animation_div;					// animation divisor
        QPointF prevPos;                    // previous position
        Inert *walkable_object;				// inert on which current entity is walking, if any
	
        // utility methods
        virtual void startJumping();
        virtual void endJumping();

	public:

		Entity();

		// getters and setters
		bool isDead() { return dead; }
		bool isDying() { return dying; }
		bool isFalling() { return falling; }
		bool isScriptMove() { return script_move; }
		

		virtual void setDirection(Direction _dir) { dir = _dir; }
		virtual void setMoving(bool _moving) { moving = _moving; }
		virtual void setFreezed(bool _freezed) { freezed = _freezed; }

		// pure virtual methods to be implemented
		virtual std::string name() = 0;
		virtual void animate() = 0;
		virtual void advance();
		virtual void solveCollisions();
		virtual void hit(Object* what, Direction fromDir) = 0;
	
		// die method, performs common operations to all entities
		// but it will need be overridden in some cases
		virtual void die();
};