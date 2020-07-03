#include "Plant.h"
#include "Mario.h"
#include "Sprites.h"

#include "Sounds.h"
Plant::Plant(QPoint position, Direction direction, bool _color, bool _cappottata) : Enemy()
{

	in_counter = 0;
	out_counter = 0;
	in = true;
	falling_counter = 0;
	jump_counter = 0;

	// set attribute
	cappottata = _cappottata;
	red = _color;
	pos_in = position;
	dir = direction;
	slow = true;  //boh po vedamo
	//falling = true;
	//jumping = false;
	// animation divisor
	animation_div = 20;

	// durations
	death_duration = 100;

	// textures
	if (!red && !cappottata) {
		texture_crunch[0] = Sprites::instance()->get("green-plant-0");
		texture_crunch[1] = Sprites::instance()->get("green-plant-1");
	}
	else if (red && !cappottata) {
		texture_crunch[0] = Sprites::instance()->get("red-plant-0");
		texture_crunch[1] = Sprites::instance()->get("red-plant-1");
	}
	else if (!red && cappottata) {
		texture_crunch[0] = Sprites::instance()->get("green-plant-0").transformed(QTransform().scale(1, -1));
		texture_crunch[1] = Sprites::instance()->get("green-plant-1").transformed(QTransform().scale(1, -1));
	}
	else if (red && cappottata) {
		texture_crunch[0] = Sprites::instance()->get("red-plant-0").transformed(QTransform().scale(1, -1));
		texture_crunch[1] = Sprites::instance()->get("red-plant-1").transformed(QTransform().scale(1, -1));
	}
	//texture_death = Sprites::instance()->get("cheep-0").transformed(QTransform().scale(-1, 1));


	// set texture and correct y-coordinate w.r.t. texture height

	setPixmap(texture_crunch[0]);

	setPos(position - QPoint(0, pixmap().height()));
	setZValue(2);
}


void Plant::advance() {
	//moving_start_counter = 0;
	//collidable = false;
	if (freezed)
		return;

	if (in) {

		//if (in_counter >= 0)
		//in_counter++;

		//if (in_counter >= 200) {
			//if (in) {
			//in_counter = 0;
		if (falling_counter >= 0)
			falling_counter++;

		if (falling_counter <= 48)

			falling_speed = (falling_counter) % 2;    //velocit� 0.5

		else if (falling_counter >= 48) {
			out_counter++;
			if (out_counter >= 200) {
				/*falling = false;
				jumping = true;*/
				in = false;
				out_counter = 0;
				falling_counter = 0;
			}
		}
		setY(y() + falling_speed);

	}




	//Game::instance()->changed_scene(level_change); ovviamente non se po fa 
	//animation_pipe = false;
	if (!in) {

		if (jump_counter >= 0)
			jump_counter++;
		if (jump_counter <= 48)
			jumping_speed = jump_counter % 2;
		else if (jump_counter >= 48) {
			in_counter++;
			if (in_counter >= 200) {
				in = true;
				/*jumping = false;
				falling = true;*/
				jump_counter = 0;
				in_counter = 0;

			}
		}
		setY(y() - jumping_speed);
	}


}



void Plant::animate()
{


	Entity::animate();

	// save current texture height (for later correction)
	int prev_h = boundingRect().height();

	// set the proper texture
	/*if (dying)
		setPixmap(texture_death);*/

	setPixmap(texture_crunch[(animation_counter / animation_div) % 2]);

	//era dello goomba perch� da morto cambiava altezza
	//// correct y position if texture height changed
	int cur_h = boundingRect().height();
	if (prev_h != cur_h)
		setY(y() - (cur_h - prev_h));


}
void Plant::hit(Object* what, Direction fromDir)
{
	Object::hit(what, fromDir);

	if ((dynamic_cast<Inert*>(what) || dynamic_cast<Enemy*>(what))
		&& (fromDir == LEFT || fromDir == RIGHT))
		dir = inverse(dir);

}

void Plant::hurt()
{
	Sounds::instance()->play("stomp");

	dying = true;
	moving = false;
}

