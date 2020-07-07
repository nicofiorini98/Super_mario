#pragma once
#include "Enemy.h"



class Piranha : public Enemy
{
private:
	//int moving_start_counter;
	int out_counter;
	int in_counter;
	
protected:
	bool rotate; 
	bool red;
	bool in;
	//bool out;
	// textures
	QPixmap texture_crunch[2];		// brown/red walk animation

	QPoint pos_in;


public:

	Piranha(QPoint position, Direction direction, bool _red, bool _rotate=false);
	// pure virtual methods that must be implemented
	virtual std::string name() { return "piranha"; }
	virtual void advance();

	virtual void animate();
	virtual void hit(Object* what, Direction direction);
	virtual void hurt();

};