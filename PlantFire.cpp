#include "PlantFire.h"
#include "Mario.h"
#include "Sprites.h"

#include "Sounds.h"
#include "Game.h"

PlantFire::PlantFire(QPoint position, Direction direction) : Enemy()
{

	in_counter = 0;
	out_counter = 0;
	in = true;
	falling_counter = 0;
	jump_counter = 0;

	// set attribute
	mario = Game::instance()->getMario();

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
	texture_crunch_up[0] = Sprites::instance()->get("plant-fire-up-0");
	texture_crunch_up[1] = Sprites::instance()->get("plant-fire-up-1");


	texture_crunch_down[0] = Sprites::instance()->get("plant-fire-down-0");
	texture_crunch_down[1] = Sprites::instance()->get("plant-fire-down-1");


	//texture_death = Sprites::instance()->get("cheep-0").transformed(QTransform().scale(-1, 1));
		//mario_up = false;

	// set texture and correct y-coordinate w.r.t. texture height

	setPixmap(texture_crunch_up[0]);

	setPos(position - QPoint(0, pixmap().height()));
	setZValue(2);
}


void PlantFire::advance() {
	//moving_start_counter = 0;
	//collidable = false;
	if (freezed)
		return;
	if (mario_left)
		dir = LEFT;
	else if (!mario_left)
		dir = RIGHT;
	if (in) {

		//if (in_counter >= 0)
		//in_counter++;

		//if (in_counter >= 200) {
			//if (in) {
			//in_counter = 0;
		if (falling_counter >= 0)
			falling_counter++;

		if (falling_counter <= 64)

			falling_speed = (falling_counter) % 2;    //velocit� 0.5

		else if (falling_counter >= 64) {
			out_counter++;

			if (out_counter >= 200) {
				/*falling = false;
				jumping = true;*/
				in = false;
				//f = new Fire_Ball(pos(), dir, 1, 0, mario_up);
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
		if (jump_counter <= 64)
			jumping_speed = jump_counter % 2;
		else if (jump_counter >= 64)
		{
			in_counter++;
			if (in_counter == 66)
				f = new FireBall(pos().toPoint() + QPoint(0, 12), dir, true, mario_up);
			if (in_counter == 133)
				f = new FireBall(pos().toPoint() + QPoint(0, 12), dir, true, mario_up);
			if (in_counter >= 200)
			{
				in = true;
				/*f = new Fire_Ball(pos(), dir, 1, 0, mario_up);*/
				/*jumping = false;
				falling = true;*/
				jump_counter = 0;
				in_counter = 0;
			}
		}
		setY(y() - jumping_speed);
	}
}



void PlantFire::animate()
{
	if (mario->pos().y() <= pos().y())
		mario_up = true;
	if (mario->pos().y() >= pos().y())
		mario_up = false;
	if (mario->pos().x() >= pos().x())
		mario_left = false;
	if (mario->pos().x() <= pos().x())
		mario_left = true;
	Entity::animate();

	// save current texture height (for later correction)
	int prev_h = boundingRect().height();

	// set the proper texture
	/*if (dying)
		setPixmap(texture_death);*/
	if (mario_up && mario_left)
		setPixmap(texture_crunch_up[(animation_counter / animation_div) % 2]);
	else if (!mario_up && mario_left)
		setPixmap(texture_crunch_down[(animation_counter / animation_div) % 2]);
	else if (!mario_up && !mario_left)
		setPixmap(texture_crunch_down[(animation_counter / animation_div) % 2].transformed(QTransform().scale(-1, 1)));
	else if (mario_up && !mario_left)
		setPixmap(texture_crunch_up[(animation_counter / animation_div) % 2].transformed(QTransform().scale(-1, 1)));

	//era dello goomba perch� da morto cambiava altezza
	//// correct y position if texture height changed
	int cur_h = boundingRect().height();
	if (prev_h != cur_h)
		setY(y() - (cur_h - prev_h));


}

void PlantFire::hit(Object* what, Direction fromDir)
{
	Object::hit(what, fromDir);

	if ((dynamic_cast<Inert*>(what) || dynamic_cast<Enemy*>(what))
		&& (fromDir == LEFT || fromDir == RIGHT))
		dir = inverse(dir);
}

void PlantFire::hurt()
{
	Sounds::instance()->play("stomp");

	dying = true;
	moving = false;
}




