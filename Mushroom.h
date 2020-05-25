//#pragma once
//
//#include "Collectable.h"
//
//class Mushroom : public Collectable
//{
//	protected:
//
//		bool red;					// whether the mushroom is red (power up) or green (life up)
//
//	public:
//
//		Mushroom(QPoint position, bool _red = true);
//
//		// inherited methods
//		virtual std::string name() {return "Mushroom";}
//		virtual void animate();
//		virtual void hit(Object *what, Direction fromDir);
//};

#pragma once

#include "Collectable.h"

class Mushroom : public Collectable
{
protected:

	bool red;					// whether the mushroom is red (power up) or green (life up)
	//todo mettere lo spawnable type
	
public:

	Mushroom(QPoint position, Direction _dir, bool _red = true);

	// inherited methods
	virtual std::string name() { return "Mushroom"; }
	virtual void animate();
	virtual void advance();
	virtual void hit(Object* what, Direction fromDir);
};
