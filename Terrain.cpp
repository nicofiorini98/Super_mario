#include "Terrain.h"
#include "Sprites.h"
#include <QPainter>

Terrain::Terrain(QRect rect) : Inert()
{
	// set position
    setPos(QPoint(rect.x(), rect.y()));

	// create collage texture
    QPixmap collage(rect.width(), rect.height());
    QPainter painter(&collage);
 
	//border
	painter.drawPixmap(0, 0, Sprites::instance()->get("ice-terrain-L"));
	painter.drawPixmap(rect.width()-16, 0, Sprites::instance()->get("ice-terrain-R"));
	// top
	for(int x=16; x<=rect.width()-32; x += 16)
		painter.drawPixmap(x, 0, Sprites::instance()->get("ice-terrain-C"));

	// end painting (necessary for setMask)
	painter.end();

	// make background color (224, 163, 216) transparent
	collage.setMask(collage.createMaskFromColor(QColor(224, 163, 216)));

	// set pixmap
    setPixmap(collage);

	// set a high z-value so it is displayed on top of other objects
	setZValue(2);
}