#pragma once

#include "Enemy.h"
#include "Coin.h"

class Muncher : public Enemy
{
	protected:
	
		// textures
		QPixmap texture_animation[3];	

		Coin* temp_coin;
	
	public:

		Muncher(QPoint position);

		// pure virtual methods that must be implemented
		virtual std::string name() {return "Muncher";}
		virtual void animate(); 
		virtual void hit(Object* what, Direction fromDir) {};
		virtual void hurt() { /* do nothing */ };
		virtual void die();
};