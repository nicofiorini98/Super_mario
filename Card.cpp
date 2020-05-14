#include "Card.h"
#include <QGraphicsScene>
#include "Sprites.h"

Card::Card(QPoint position, const std::string& _id, QGraphicsScene* scene)
{
	id = _id;

	texture_item = Sprites::instance()->get(id + "-card");
	
	scene->addItem(this);
	setPos(position);
	setPixmap(texture_item);
}