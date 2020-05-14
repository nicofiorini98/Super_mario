#include "Mario.h"
#include "Sounds.h"
#include "Leaf.h"
#include "Sprites.h"
#include <iostream>
Leaf::Leaf(QPoint position, Direction _dir) : Collectable(position)
{
	// set attributes
	type = LEAF;
	dir = _dir;
	// set texture and position
	setPixmap(Sprites::instance()->get(""));//todo istanziare la texture della foglia
	
	setPos(position);
	
	setZValue(1);
	// play mushroom sound
	Sounds::instance()->play("spawn");
}

void Leaf::animate()
{
	Entity::animate();


}

void Leaf::hit(Object* what, Direction fromDir)
{
	Object::hit(what, fromDir);

	// if hit by Mario, Mario eats mushroom and mushroom dies
	Mario* mario = dynamic_cast<Mario*>(what);
	if (mario)
	{
		//todo farlo in mario
		//mario->setFire(true);
		die();
		return;
	}
	Inert* inert_obj = dynamic_cast<Inert*>(what);
	if (inert_obj && fromDir == DOWN)
		walkable_object = inert_obj;

	// if hit from its left or right side, it
	// has to move to the opposite direction w.r.t. the one
	// is he currently moving
}


void Leaf::advance()
{

	//todo fare lo script della foglia
	
}