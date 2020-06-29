#include "KoopaTroopa.h"
#include <iostream>
#include "Sprites.h"
#include "Sounds.h"


KoopaTroopa::KoopaTroopa(QPoint position, Direction direction) : Enemy()
{

	pos_in = position;
	dir = direction;
	slow = true;
	falling = true;
	normal = true;
	shell = false;
	shell_moving = false;
	shell_counter = -1;
	shell_duration = 400;
	// animation divisor
	animation_div = 8;

	// durations
	death_duration = 100;

	// textures
	texture_walk[0] = Sprites::instance()->get("Koopa_Troopa-0");
	texture_walk[1] = Sprites::instance()->get("Koopa_Troopa-1");
	texture_shell = Sprites::instance()->get("Blocked-Shell");
	texture_shell_moving[0] = Sprites::instance()->get("Shell-moving-0");
	texture_shell_moving[1] = Sprites::instance()->get("Shell-moving-1");
	texture_shell_moving[2] = Sprites::instance()->get("Shell-moving-2");
	texture_shell_moving[3] = Sprites::instance()->get("Shell-moving-3");
	texture_death = Sprites::instance()->get("Blocked-Shell").transformed(QTransform().scale(-1, 1));
	// set texture and correct y-coordinate w.r.t. texture height

	setPixmap(texture_walk[0]);

	setPos(position - QPoint(0, pixmap().height()));

	setZValue(2);
}

void KoopaTroopa::advance()
{
	if (normal) {
		Entity::advance();
		moving = true;
		slow = true;
	}
	else if (shell) {
		moving = false;
		shell_counter++;
	}
	else if (shell_moving) {
		Entity::advance();
		moving_speed = 2;
		moving = true;
		slow = false;
		shell_counter = -1;
	}
}

void KoopaTroopa::animate()
{
	if (shell_counter >= 0) {
		shell_counter++;
		std::cout << shell_counter << std::endl;
		if (shell_counter >= shell_duration) {
			shell = false;
			normal = true;
			shell_counter = -1;
		}

	}


	Entity::animate();

	// save current texture height (for later correction)
	int prev_h = boundingRect().height();

	// set the proper texture
	if (dying)
		setPixmap(texture_death);
	else if (moving && normal)
		setPixmap(texture_walk[(animation_counter / animation_div) % 2]);
	else if (shell)
		setPixmap(texture_shell);
	else if (shell_moving && moving)
		setPixmap(texture_shell_moving[(animation_counter / animation_div) % 4]);
	//questo serve per quando diventa guscio
	int cur_h = boundingRect().height();
	if (prev_h != cur_h)
		setY(y() - (cur_h - prev_h));
	if (dir == RIGHT)
		setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
}

void KoopaTroopa::hit(Object* what, Direction fromDir)
{

	Object::hit(what, fromDir);

	if ((dynamic_cast<Inert*>(what) || dynamic_cast<Enemy*>(what))
		&& (fromDir == LEFT || fromDir == RIGHT))
		dir = inverse(dir);
	if (dynamic_cast<Mario*>(what) && fromDir == UP && normal) {

		normal = false;
		shell = true;
		shell_counter++;
	}
	else if (dynamic_cast<Mario*>(what) && shell) {
		shell = false;
		shell_moving = true;
	}
	else if (dynamic_cast<Mario*>(what) && fromDir == UP && shell_moving) {


		shell_moving = false;
		shell = true;
		shell_counter++;
	}
}

void KoopaTroopa::hurt()
{
	Sounds::instance()->play("stomp");
	dying = true;
	moving = false;
}






QPainterPath KoopaTroopa::shape() const
{
	QPainterPath path;
	////path.addRect(0, boundingRect().top() , boundingRect().width(), boundingRect().bottom() );
	if (normal)
		path.addRect(0, boundingRect().top() + 11, boundingRect().width(), boundingRect().bottom() - 11);
	else path.addRect(0, boundingRect().top(), boundingRect().width(), boundingRect().bottom());
	return path;
}