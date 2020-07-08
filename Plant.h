#pragma once
#include "Enemy.h"


class Plant : public Enemy
{
private:
	

protected:

	//int moving_start_counter;
	int out_counter;
	int in_counter;
	bool rotate;
	bool red;
	bool in;
	
	// dying is in common for all plants
	QPixmap texture_dying[12];
	QPoint pos_in;

public:

	Plant();
	
	virtual void advance();
	virtual void animate();
	virtual void hit(Object* what, Direction direction);
	
	// pure virtual methods that must be implemented
	virtual std::string name() = 0;
	virtual void hurt() = 0;

};