#pragma once
#include "Entity.h"
enum spawnable_t
{
	DEBUG,
	COIN,
	MUSHROOM,
	LEAF,
	LIFE,
	FLOWER,
	STAR
};

class Collectable : public Entity
{
	protected:
		
		QPoint spawned_position;	// position where collectable spawned
		spawnable_t type;			//type of item that spawned
	public:

		Collectable(QPoint position);

		// inherited methods
		virtual std::string name() = 0;
		virtual void animate() = 0;
		virtual void hit(Object *what, Direction fromDir) = 0;
};