#include "Iceberg.h"
#include "Sprites.h"

#include <QPainter>

Iceberg::Iceberg(QRect rect, std::string _level_name,std::string type, std::string pos_rel_to_water_lvl ) : Inert()   
{
	level_name = _level_name;
	_type = type;

	// set position
	setPos(rect.x(), rect.y());

	// create collage texture
	QPixmap  collage(rect.width(), rect.height());
	QPainter painter(&collage);

	if (_type == "vert-right-edge")
		for (int y = 0; y <= rect.height() - 16; y += 16)
			painter.drawPixmap(0, y, Sprites::instance()->get(pos_rel_to_water_lvl  + name()  + "-E"));

	else if (_type == "vert-left-edge")
		for (int y = 0; y <= rect.height() - 16; y += 16)
			painter.drawPixmap(0, y, Sprites::instance()->get(pos_rel_to_water_lvl  + name() + "-W"));

	else if (_type == "horiz-top-edge")
		for (int x = 0; x <= rect.width() - 16; x += 16)
			painter.drawPixmap(x, 0, Sprites::instance()->get(pos_rel_to_water_lvl + name() + "-N"));

	else if (_type == "horiz-bottom-edge")
		for (int x = 0; x <= rect.width() - 16; x += 16)
			painter.drawPixmap(x, 0, Sprites::instance()->get(pos_rel_to_water_lvl + name() + "-S"));


	else if (_type == "vert-right-edge1")
	{
		painter.drawPixmap(0, 0, Sprites::instance()->get(pos_rel_to_water_lvl  + name() + "-NE"));
		for (int y = 16; y <= rect.height() - 16; y += 16)
			painter.drawPixmap(0, y, Sprites::instance()->get(pos_rel_to_water_lvl  + name() + "-E"));
	}
	else if (_type == "vert-left-edge1")
	{
		painter.drawPixmap(0, 0, Sprites::instance()->get(pos_rel_to_water_lvl  + name() + "-NW"));
		for (int y = 16; y <= rect.height() - 16; y += 16)
			painter.drawPixmap(0, y, Sprites::instance()->get(pos_rel_to_water_lvl + name() + "-W"));
	}
	else if (_type == "horiz-top-edge1")
	{
		painter.drawPixmap(0, 0, Sprites::instance()->get(pos_rel_to_water_lvl  + name() + "-NW"));
		for (int x = 16; x <= rect.width() - 16; x += 16)
			painter.drawPixmap(x, 0, Sprites::instance()->get(pos_rel_to_water_lvl  + name() + "-N"));
	}
	else if (_type == "horiz-bottom-edge1")
	{
		painter.drawPixmap(0, 0, Sprites::instance()->get(pos_rel_to_water_lvl  + name() + "-SW"));
		for (int x = 16; x <= rect.width() - 16; x += 16)
			painter.drawPixmap(x, 0, Sprites::instance()->get(pos_rel_to_water_lvl  + name() + "-S"));
	}

	
	else if (_type == "horiz-bottom-edge2")
	{
		for (int x = 0; x <= rect.width() - 32; x += 16)
			painter.drawPixmap(x, 0, Sprites::instance()->get(pos_rel_to_water_lvl  + name() + "-S"));
		painter.drawPixmap(rect.width() - 16, 0, Sprites::instance()->get(pos_rel_to_water_lvl  + name() + "-SE"));
	}
	else if (_type == "horiz-top-edge2")
	{
		for (int x = 0; x <= rect.width() - 32; x += 16)
			painter.drawPixmap(x, 0, Sprites::instance()->get(pos_rel_to_water_lvl  + name() + "-N"));
		painter.drawPixmap(rect.width() - 16, 0, Sprites::instance()->get(pos_rel_to_water_lvl  + name() + "-NE"));
	}
	else if (_type == "vert-right-edge2")
	{
		for (int y = 0; y <= rect.height() - 32; y += 16)
			painter.drawPixmap(0, y, Sprites::instance()->get(pos_rel_to_water_lvl  + name() + "-E"));
		painter.drawPixmap(0, rect.height() - 16, Sprites::instance()->get(pos_rel_to_water_lvl  + name() + "-SE"));
	}
	else if (_type == "vert-left-edge2")
	{
		for (int y = 0; y <= rect.height() - 32; y += 16)
			painter.drawPixmap(0, y, Sprites::instance()->get(pos_rel_to_water_lvl  + name() + "-W"));
		painter.drawPixmap(0, rect.height() - 16, Sprites::instance()->get(pos_rel_to_water_lvl  + name() + "-SW"));
	}


	else if (_type == "downhill")
		painter.drawPixmap(0, 0, Sprites::instance()->get("downhill"));
	else if (_type == "uphill")
		painter.drawPixmap(0, 0, Sprites::instance()->get("uphill"));
	else if (_type == "downhill2")
		painter.drawPixmap(0, 0, Sprites::instance()->get("downhill2"));
	
	// end painting (necessary for setMask)
	painter.end();

	if (_type == "downhill" || _type == "uphill" || _type == "downhill2")
		collage.setMask(collage.createMaskFromColor(QColor(237, 28, 36)));   // make background color (237, 28, 36)  transparent
	
	setPixmap(collage);
		
	setZValue(2);
}
std::string Iceberg::name()
{
	return level_name == "World 6-9-2" ? "Iceberg1" : "Iceberg2";
}