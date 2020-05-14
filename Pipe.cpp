#include "Pipe.h"
#include "Sprites.h"

#include <QPainter>

Pipe::Pipe(QPoint position, std::string _level_name, int height, std::string rotation) : Inert()
{

	level_name = _level_name;

	// set position
	setPos(QPoint(position.x(), position.y()-(1+height)*16));
	 
	setTransformOriginPoint(16, (1 + height) * 16);

	// create collage texture
	QPixmap collage(32, (1+ height)*16);
	QPainter painter(&collage);

	// entrance
	painter.drawPixmap( 0, 0, Sprites::instance()->get(rotation + name() + "-NW"));
	painter.drawPixmap(16, 0, Sprites::instance()->get(rotation + name() + "-NE"));
	
	// pipe
	for (int i = 1; i <= height; i++)
	{
		painter.drawPixmap( 0, i * 16, Sprites::instance()->get(rotation + name() + "-W"));
		painter.drawPixmap(16, i * 16, Sprites::instance()->get(rotation + name() + "-E"));
	}

	// end painting (necessary for setMask)
	painter.end();

	// make background color (224, 163, 216) transparent
	collage.setMask(collage.createMaskFromColor(QColor(224, 163, 216)));

	setPixmap(collage);
	
	setZValue(3);		
}

std::string Pipe::name()
{
	return level_name == "World 6-9-1"  ?  "pipe1" : level_name == "World 6-9-2"  ?  "pipe2" : "pipe3";
}

void Pipe::hit(Object *what, Direction fromDir)
{
	Object::hit(what, fromDir);
}