#pragma once
#include "Enemy.h"
#include "Mario.h"
#include "Game.h"

class KoopaTroopa : public Enemy
{
protected:
	Mario* mario;

	// attributes
	bool normal;                 //is koopatroopa normally walking?
	bool shell;                  //is koopatroopa in shell and not moving ?
	bool shell_moving;           //is koopatroopa in shell moving?
	bool harmless;               //is koopatroopa harmless?
            

	//physics parameters for koopatroopa's shell state
	int shell_counter;           
	int shell_duration;


	// textures
	QPixmap texture_walk[2];
	QPixmap texture_shell;
	QPixmap texture_shell_moving[4];
	QPixmap texture_death;
	QPoint pos_in;
	//@ovverride QPainter
	QPainterPath shape() const;
public:

	KoopaTroopa(QPoint position, Direction direction = LEFT);
	bool isShell() { return (shell || (shell_moving && harmless)); }
	int isShelling() { return shell_counter; }
	bool isShellMoving() { return shell_moving; }
	// pure virtual methods that must be implemented
	virtual std::string name() { return "KoopaTroopa"; }
	virtual void animate();
	virtual void hit(Object* what, Direction fromDir);
	virtual void hurt();
	virtual void advance();
};