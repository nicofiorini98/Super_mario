#pragma once
#include "Enemy.h"
#include "Mario.h"

class KoopaTroopa : public Enemy
{
protected:

	// attributes
	bool normal;
	bool shell;
	bool shell_moving;

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
	bool isShell() { return shell; }
	bool isShellMoving() { return shell_moving; }
	// pure virtual methods that must be implemented
	virtual std::string name() { return "KoopaTroopa"; }
	virtual void animate();
	virtual void hit(Object* what, Direction fromDir);
	virtual void hurt();
	virtual void advance();
};