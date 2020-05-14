#pragma once

#include <string>
#include <QGraphicsPixmapItem>

#include "utils.h"

// base class for all game objects
class Object : public QGraphicsPixmapItem
{	
	protected:

		bool collidable;		// whether the object is collidable
		bool collider_visible;	// whether the collider is visible

		std::string level_name; // level where object is located

	public:

		Object();

		// getters
		bool isCollidable() {return collidable;}
		void setLevelName(std::string _level_name) { level_name = _level_name; }
		std::string getLevelName() { return level_name; }

        // object name
		virtual std::string name() = 0;

        // animate (=compute next texture)
        virtual void animate() = 0;

        // advance (=compute next location)
        virtual void advance() = 0;

        // solve collisions
        virtual void solveCollisions() = 0;

        // object hit by 'what' from direction 'fromDir'
		virtual void hit(Object *what, Direction fromDir) = 0;

        // utility methods: detect collision/touching direction
        virtual Direction collisionDirection(Object* item);
        virtual Direction touchingDirection(Object* item);

		// show / hide collider
		void toogleColliderVisible();
};
