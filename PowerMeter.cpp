#include "PowerMeter.h"
#include "Sprites.h"
#include <iostream>
#include "Sounds.h"

PowerMeter::PowerMeter()
{
	texture_arrow[0] = Sprites::instance()->get("arrow");
	texture_arrow[1] = Sprites::instance()->get("arrow-transparent");
	texture_arrow[2] = Sprites::instance()->get("P");
	texture_arrow[3] = Sprites::instance()->get("P-transparent");

	for (int i = 0; i < 7; i++)
	{
		pan.push_back(new QGraphicsPixmapItem());
		if (i < 6)
			pan[i]->setPos(57 + 8 * i, 9);//todo da aggiustare sicuramente
		else
			pan[i]->setPos(106, 9);

		addToGroup(pan[i]);
	}


	std::string prova = "33";


}

void PowerMeter::reset()
{
	pan[0]->setPixmap(texture_arrow[1]);
	pan[1]->setPixmap(texture_arrow[1]);
	pan[2]->setPixmap(texture_arrow[1]);
	pan[3]->setPixmap(texture_arrow[1]);
	pan[4]->setPixmap(texture_arrow[1]);
	pan[5]->setPixmap(texture_arrow[1]);
	pan[6]->setPixmap(texture_arrow[3]);
}


void PowerMeter::doUpdate(const std::string& update_info)
{

	speed = std::stoi(update_info);

	if (speed == 0)
	{
		reset();
		return;
	}


	for (int i = 0; i < speed; i++)					//turn on arrow
		pan[i]->setPixmap(texture_arrow[0]);

	for (int i = speed; i < 6; i++)					//turn of arrow
		pan[i]->setPixmap(texture_arrow[1]);

	if (speed == 7)		
		pan[6]->setPixmap(texture_arrow[2]);
	else											//turn off P
		pan[6]->setPixmap(texture_arrow[3]);

}
