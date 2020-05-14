#pragma once

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Card : public QGraphicsPixmapItem
{
	
	private:

		std::string id;
		QPixmap texture_item;

	public:

		Card(QPoint position, const std::string& _id, QGraphicsScene* scene);

		// getters
		std::string name() { return "Card"; }
		std::string getId() const { return id; }	
};