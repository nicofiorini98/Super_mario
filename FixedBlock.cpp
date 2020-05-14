#include "FixedBlock.h"
#include "Sprites.h"
#include <QPainter>
#include <iostream>

FixedBlock::FixedBlock(QPoint pos, std::string _type) : Inert()
{

	if (_type != "ice" && _type != "wood")
		std::cerr << "Type not valid\n";
	
	// set position
	setPos(pos);

	if (_type == "ice")
	{
		// create collage texture
		QPixmap collage(32, 32);
		QPainter painter(&collage);

		//border
		painter.drawPixmap( 0,  0, Sprites::instance()->get("ice-block-NW"));
		painter.drawPixmap(16,  0, Sprites::instance()->get("ice-block-NE"));
		painter.drawPixmap( 0, 16, Sprites::instance()->get("ice-block-SW"));
		painter.drawPixmap(16, 16, Sprites::instance()->get("ice-block-SE"));

		// end painting (necessary for setMask)
		painter.end();

		// make background color (224, 163, 216) transparent
		collage.setMask(collage.createMaskFromColor(QColor(224, 163, 216)));

		// set pixmap
		setPixmap(collage);
	}
	else 
	{
		
		QPixmap pixmap = Sprites::instance()->get("wood-block");

		// make background color (224, 163, 216) transparent
		pixmap.setMask(pixmap.createMaskFromColor(QColor(224, 163, 216)));

		setPixmap(pixmap);
	}


	// set a high z-value so it is displayed on top of other objects
	setZValue(2);
}