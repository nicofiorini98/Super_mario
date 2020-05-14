#pragma once

#include "Enemy.h"

class KoopaTroopa : public Enemy
{
	private:

		QPixmap texture_animation[4]; // rivedere numero corretto delle textures

	public:

		KoopaTroopa(QPoint position);

		virtual std::string name() { return "KoopaTroopa"; }
		virtual void advance();
		virtual void animate();
		virtual void hit(Object* what, Direction fromDir);
		virtual void hurt();

};