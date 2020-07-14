#include <QKeyEvent>
#include <QWheelEvent>

#include "Game.h"
#include "Object.h"
#include "Entity.h"
#include "Mario.h"
#include "Sounds.h"
#include "Sprites.h"
#include "Hud.h"
#include "Enemy.h"
#include "SwitchBlock.h"
#include "EndLevelText.h"
#include "Card.h"
#include <iostream>

// Singleton design pattern
Game* Game::uniqueInstance = nullptr;
Game* Game::instance(QWidget* parent)
{
	if (uniqueInstance == 0)
		uniqueInstance = new Game(parent);
	return uniqueInstance;
}


Game::Game(QWidget* parent) : QGraphicsView(parent)
{
	// setup scene/view
	scene1 = new QGraphicsScene();
	scene2 = nullptr;
	scene3 = nullptr;
	black_scene = nullptr;
	cur_scene = scene1;
	//todo check it
	
	lives = 4;
	score = 0;
	
	scale(3.0, 3.0);
	centerOn(0, 0);
	
	setFrameShape(QFrame::NoFrame);
	setInteractive(false);		// disables events
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	
	// setup game music
	
	music1      = new QSound(":/sounds/overworld.wav");
	music2      = new QSound(":/sounds/underwater.wav");
	music3      = new QSound(":/sounds/super-mario-rap.wav");
	fast_music1 = new QSound(":/sounds/overworld-hurry-up.wav");
	fast_music2 = new QSound(":/sounds/underwater-hurry-up.wav");
	fast_music3 = new QSound(":/sounds/underground-hurry-up.wav");
	music1->setLoops(QSound::Infinite);
	music2->setLoops(QSound::Infinite);
	music3->setLoops(QSound::Infinite);
	//fast_music1->setLoops(QSound::Infinite);
	
	fast_music2->setLoops(QSound::Infinite);
	fast_music3->setLoops(QSound::Infinite);

	// initialize mario
	mario = nullptr;
	spinning_item = nullptr;
	
	// flags
	hurry_up = false;
	key_up_pressed = false;

	// counter
	clear_level_counter = -1;
	
	// setup game time
	game_time = new QTimer(this);
	game_time->setInterval(600);

	// reset game
	reset();

	// setup game engine 
	QObject::connect(&engine, SIGNAL(timeout()), this, SLOT(advance()));
	engine.setInterval(15);
	

	// setup window size
	this->setFixedHeight(602);
	this->setFixedWidth(3*16*16);
}

// reset game
void Game::reset()
{
	cur_state = READY;
	cur_scene = scene1;
	setScene(cur_scene);

	mario = nullptr;
	engine.stop();

	game_time->stop();
	if(game_time->interval() == 2)
		game_time->setInterval(600);

	stopMusic();

	if(hurry_up)
		hurry_up = false;
	
	// clear 
	scene1->clear();
	if (scene2)
	{
		scene2->clear();
		scene2 = nullptr;
	}
	if (scene3)
	{
		scene3->clear();
		scene3 = nullptr;
	}
	grid.clear();

	if (clear_level_counter >= 0)
		clear_level_counter = -1;
	
	// display welcome message  
	cur_scene->setBackgroundBrush(QBrush(Qt::black));
	cur_scene->addPixmap(Sprites::instance()->get("main-screen"));
	centerOn(0, 0);
}


void Game::gameover()
{
	if(!mario->isDead())
	{
		if (!mario->isDying())
			mario->die();

		// set black background
		cur_scene->setBackgroundBrush(QBrush(Qt::black));

		//  stop music and play game over sound
		stopMusic();

		Sounds::instance()->play("gameover");
	}
	else
	{
		// stop game
		cur_state = GAME_OVER;
		engine.stop();
		game_time->stop();
		
		//update attributes
		lives = mario->getLives() - 1;
		score = mario->getScore();

	}
	
}

// start new game
void Game::start()
{
	if (cur_state == READY)
	{
		scene1->clear();
		engine.start();
		game_time->start();
		
		cur_level_name = "World 6-9-1";

		// load level
		mario = LevelManager::load(cur_level_name,scene1);

		Hud::instance()->start();
		
		//update attribbute
		mario->updateLives(lives);
		mario->updateScore(score);

		// add debug grid                                                        
		for (int i = 0; i <= 27; i++)
			grid.push_back(new QGraphicsLineItem(0, i*16, 127*16, i*16));
		for (int j = 0; j <= 97; j++)
			grid.push_back(new QGraphicsLineItem(j*16, 0, j*16, 27*16));

		for (auto& l : grid)
		{
			l->setPen(QPen(QBrush(Qt::gray), 0.5));
			l->setZValue(100);
			cur_scene->addItem(l);
			l->setVisible(false);
		}

		if (!mario)
		{
			cur_scene->setBackgroundBrush(QBrush(QColor(242, 204, 204)));
			QGraphicsTextItem* text = cur_scene->addText("Error when loading level");
			text->setPos(300, 90);
			centerOn(text);
		}
		else
			music1->play();

		cur_state = RUNNING;
	}
}

// pause / resume game
void Game::tooglePause()
{
	if (cur_state == RUNNING)
	{
		engine.stop();
		stopMusic();
		cur_state = PAUSE;
		Sounds::instance()->play("pause");
	}
	else if (cur_state == PAUSE)
	{
		engine.start();
		playMusic();
		cur_state = RUNNING;
	}
}

// show/ hide level grid
void Game::toogleGrid()
{
	for (auto& l : grid)
		l->setVisible(!l->isVisible());
}

// show/ hide object colliders
void Game::toogleColliders()
{
	for (auto& item : cur_scene->items())
		if (dynamic_cast<Object*>(item))
			dynamic_cast<Object*>(item)->toogleColliderVisible();
}

// play music
void Game::playMusic()
{
	if (hurry_up)
		(cur_level_name=="World 6-9-1") ? fast_music1->play() : (cur_level_name=="World 6-9-2") ? fast_music2->play() : fast_music3->play();
	else 
		(cur_level_name=="World 6-9-1") ? music1->play() : (cur_level_name=="World 6-9-2") ? music2->play() : music3->play();
}

// stop music
void Game::stopMusic()
{
	if (hurry_up)
		(cur_level_name == "World 6-9-1") ? fast_music1->stop() : (cur_level_name == "World 6-9-2") ? fast_music2->stop() : fast_music3->stop();
	else
		(cur_level_name == "World 6-9-1") ? music1->stop() : (cur_level_name == "World 6-9-2") ? music2->stop() : music3->stop();
}

void Game::keyPressEvent(QKeyEvent* e)
{
	// ignore auto repeat key pressed/released
	// (same key has been pressed before and we already processed it)
	if (e->isAutoRepeat())
		return;

	// start new game
	if (e->key() == Qt::Key_Return && cur_state == READY)
		start();

	// reset game and hud
	if ((e->key() == Qt::Key_R || cur_state == GAME_OVER) && !SwitchBlock::SwitchEffect())
	{
		Hud::instance()->reset();
		this->reset();
	}

	// pause game
	if (e->key() == Qt::Key_P)
		tooglePause();

	// show/hide grid game
	if (e->key() == Qt::Key_G)
		toogleGrid();

	// show/hide colliders
	if (e->key() == Qt::Key_C)
		toogleColliders();

	// from now on, all commands require the game to be running
	if (cur_state != RUNNING)
		return;

	// speed up / slow down
	if (e->key() == Qt::Key_Plus)
		engine.setInterval(engine.interval() / 5);
	if (e->key() == Qt::Key_Minus)
		engine.setInterval(engine.interval() * 5);

	// horizontal Mario's movements
	if (e->key() == Qt::Key_Right || e->key() == Qt::Key_Left)
	{
		mario->setDirection(e->key() == Qt::Key_Right ? Direction::RIGHT : Direction::LEFT);
		mario->setMoving(true);
	}
	
	if (e->key() == Qt::Key_Up)
		key_up_pressed = true;
	
	if (e->key() == Qt::Key_Down)
	{
		if (mario->isOnPipe(cur_level_name))
		{
			cur_state = CHANGE_LEVEL;
			mario->enterPipe(Direction::UP);
		}
		else
			mario->setCrouch(true);
	}
		
	
	// Mario's jump
	if (e->key() == Qt::Key_Space)
	{
		//mario is swimming
		if (mario->isInWater())
			mario->swim();
		//mario is rebounding on jumpblock
		else if (mario->isBouncing())
			mario->setRebound(true);
		//mario raccoon is flying
		else if (mario->isRaccoon() && mario->isSuperRunning())
			mario->fly();
		else
			mario->jump();
	}
		
	// Mario's running
	if (e->key() == Qt::Key_Z)
		mario->setRunning(true);

	// Mario's transformation
	if (e->key() == Qt::Key_T)
		mario->powerUp(DEBUG); 

		//Mario's shooting
	if (e->key() == Qt::Key_B)
		mario->setAttack(true);

	// hurt every enemy
	if (e->key() == Qt::Key_H)
		for (auto& item : cur_scene->items())
		{
			Enemy* obj = dynamic_cast<Enemy*>(item);
			if (obj)
				obj->hurt();
		}
}

void Game::keyReleaseEvent(QKeyEvent* e)
{
	// ignore auto repeat key pressed/released
	// (same key has been pressed before and we already processed it)
	if (e->isAutoRepeat())
		return;

	if (e->key() == Qt::Key_Up)
		key_up_pressed = false;

	// from now on, all commands require the game to be running
	if (cur_state != RUNNING)
		return;

	// horizontal Mario's movements
	if (e->key() == Qt::Key_Right || e->key() == Qt::Key_Left)
		mario->setMoving(false);
	
	if (e->key() == Qt::Key_Down)
		mario->setCrouch(false);

	// Mario's running
	if (e->key() == Qt::Key_Z)
		mario->setRunning(false);
}

// zoom-in/out
void Game::wheelEvent(QWheelEvent* e)
{
	if (e->delta() > 0)
		scale(1.1, 1.1);
	else
		scale(1 / 1.1 ,1 / 1.1);
}

void Game::advance()
{
	// do nothing if game is not running
	if (cur_state != RUNNING && cur_state != CHANGE_LEVEL && cur_state != END_OF_LEVEL)
		return;

	if (mario->isEnteringPipe())
	{
		cur_state = CHANGE_LEVEL;
	}

	// if mario is dead, game over
	if (mario->isDead() && cur_state != CHANGE_LEVEL)
		gameover();

	// tell all game objects to animate and advance in the scene
	for (auto& item : cur_scene->items())
	{
		
		Object* obj = dynamic_cast<Object*>(item);
		if (obj)
		{
			obj->animate();
			obj->advance();

			// destroy died Entity objects, except Mario
			Entity* entity_obj = dynamic_cast<Entity*>(obj);
			Mario*  mario_obj  = dynamic_cast<Mario*>(obj);
			if (entity_obj && !mario_obj && entity_obj->isDead())
			{
				cur_scene->removeItem(entity_obj);
				delete entity_obj;
			}
		}
	}

	if (cur_state != END_OF_LEVEL) 
	{
		if (!mario->isRaccoonAttack() && !mario->isDying())// center view on shape of Mario
			centerOn(QPointF(mario->pos().x() + mario->shape().currentPosition().x(), mario->pos().y()+mario->boundingRect().height()));
	}
	else
	{
			centerOn(QPointF(88 * 16, 337));  // center view on GoalRoulette

			if (mario->pos().x() >= 96 * 16)
			{
				clear_level_counter++;

				if (clear_level_counter == 0)
					new EndLevelText(QPoint(1337, 267), "CLEAR COURSE!");

				if (clear_level_counter == 23)
					new EndLevelText(QPoint(1337, 294), "YOU GOT A CARD");

				else if (clear_level_counter == 43)
				{
					new Card(QPoint(1464, 299), mario->ItemTaken(), scene1);
					Hud::instance()->updatePanel("CardsTaken", mario->ItemTaken());
					
				}
				else if (clear_level_counter == 170)
					fastResetOfGameTime();

				else if (clear_level_counter == 300)
				{
					Hud::instance()->reset();
					lives = mario->getLives();
					score = mario->getScore();
					reset();
				}
			}
		
	}
	// here we have to report to 000 the hud timer 
}

// freeze/unfreeze all entities
void Game::setFreezed(bool freezed)
{
	// tell all game objects to animate and advance in the scene
	for (auto& item : cur_scene->items())
	{
		Entity* entity_obj = dynamic_cast<Entity*>(item);
		Mario*   mario_obj = dynamic_cast<Mario*>(item);
		if (cur_state == CHANGE_LEVEL && !mario_obj && entity_obj)
			entity_obj->setFreezed(freezed);
		else if(entity_obj)
			entity_obj->setFreezed(freezed);
	}

	if (freezed == false && cur_state == CHANGE_LEVEL)
		cur_state = RUNNING;
}

void Game::changeLevel(Direction pipe_travel_dir)
{
	engine.stop();
	stopMusic();

	// set black screen
	if (!black_scene)
	{
		black_scene = new QGraphicsScene();
		black_scene->setBackgroundBrush(QBrush(QColor(0, 0, 0)));
	}
	else
		setScene(black_scene);

	Hud::instance()->hide();

	// after 200 ms the screen has been obscured show it again
	QTimer::singleShot(200, this, [this]() { engine.start(); setScene(cur_scene); Hud::instance()->show(); playMusic(); });
	
	if (pipe_travel_dir == DOWN)
		nextLevel();
	else if (pipe_travel_dir == UP)
		prevLevel();

}

void Game::nextLevel()
{
	cur_level_name = ((mario->getLevelName() == "World 6-9-1") ? "World 6-9-2" : "World 6-9-3");
	
	if (cur_level_name == "World 6-9-2")
	{

		scene1->removeItem(mario);
		if (!scene2)
		{
			scene2 = new QGraphicsScene();
			cur_scene = scene2;
			LevelManager::load(cur_level_name, cur_scene);
		}
		else cur_scene = scene2;	

	}
	else if (cur_level_name == "World 6-9-3" )
	{
		scene2->removeItem(mario);
		if (!scene3)
		{
			scene3 = new QGraphicsScene();
			cur_scene = scene3;
			LevelManager::load(cur_level_name, cur_scene);
		}
		else cur_scene = scene3;	
	}
	
	cur_scene->addItem(mario);
	mario->setLevelName(cur_level_name);
	mario->setPos(((cur_level_name == "World 6-9-2" ? 4 : 8)*16)+5, 0);	
}

void Game::prevLevel()
{
	cur_level_name = ((mario->getLevelName() == "World 6-9-3") ? "World 6-9-2" : "World 6-9-1");

	(mario->getLevelName() == "World 6-9-3") ? scene3->removeItem(mario) : scene2->removeItem(mario);

	cur_scene = (mario->getLevelName() == "World 6-9-3") ? scene2 : scene1;

	cur_scene->addItem(mario);
	mario->setLevelName(cur_level_name);
	
	if (mario->isRaccoon())
		mario->setPos(((cur_level_name == "World 6-9-2" ? 70 : 52) * 16) + 5, ((cur_level_name == "World 6-9-2" ? 25 : 25) * 16) - 4);
	else
		mario->setPos( ((cur_level_name=="World 6-9-2" ? 70:52) * 16)+5, ((cur_level_name=="World 6-9-2" ? 25:25) * 16)-2);
	
}

void Game::hurryUp()
{
	stopMusic();

	// from now on, 100 seconds are left to game-time's end
	hurry_up = true;

	// play "hurry-up" sound to warn that the player is running low on time 
	Sounds::instance()->play("hurry-up");

	// when "hurry-up" jingle is finished, 
	// play level's music at a faster speed
	QTimer::singleShot(2850, this, [this]() { playMusic(); });
}

void Game::endLevel()
{
	cur_state = END_OF_LEVEL;
	stopMusic();
	Sounds::instance()->play("levelend");
}

void Game::stopGameTime()
{
	game_time->stop();
}

std::string Game::state2str()
{
	if (cur_state == READY)
		return "READY";
	else if (cur_state == RUNNING)
		return "RUNNING";
	else if (cur_state == PAUSE)
		return "PAUSE";
	else if (cur_state == GAME_OVER)
		return "GAME_OVER";
	else if (cur_state == CHANGE_LEVEL)
		return "CHANGE_LEVEL";
	else
		return "END_OF_LEVEL";
}

void Game::fastResetOfGameTime()
{
	game_time->setInterval(2);
	game_time->start();
	Sounds::instance()->play("timer-reset");
}