#include "PowerMeter.h"
#include "Sprites.h"

PowerMeter::PowerMeter()
{
	texture_arrow[0] = Sprites::instance()->get("arrow");
	texture_arrow[1] = Sprites::instance()->get("arrow-transparent");
	texture_arrow[2] = Sprites::instance()->get("P");
	texture_arrow[3] = Sprites::instance()->get("P-transparent");

	for (int i = 0; i < 7; i++)
	{
		pan.push_back(new QGraphicsPixmapItem());
		if(i<6)
			pan[i]->setPos(57 + 8 * i, 9);//todo da aggiustare sicuramente
		else
			pan[i]->setPos(106, 9);
		
		addToGroup(pan[i]);
	}

	reset();
	
}

void PowerMeter::reset()
{
	pan[0]->setPixmap(texture_arrow[0]);
	pan[1]->setPixmap(texture_arrow[0]);
	pan[2]->setPixmap(texture_arrow[0]);
	pan[3]->setPixmap(texture_arrow[0]);
	pan[4]->setPixmap(texture_arrow[0]);
	pan[5]->setPixmap(texture_arrow[0]);
	pan[6]->setPixmap(texture_arrow[2]);
	
}


void PowerMeter::doUpdate(const std::string& update_info)
{
	
}