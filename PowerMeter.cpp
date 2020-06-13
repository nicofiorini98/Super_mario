#include "PowerMeter.h"
#include "Sprites.h"
#include <iostream>
//#include <QObject>

PowerMeter::PowerMeter()
{
	speed = 0;


	texture_arrow[0] = Sprites::instance()->get("arrow");
	texture_arrow[1] = Sprites::instance()->get("arrow-transparent");
	texture_arrow[2] = Sprites::instance()->get("P");
	texture_arrow[3] = Sprites::instance()->get("P-transparent");

	for (int i = 0; i < 7; i++)
	{
		pan.push_back(new QGraphicsPixmapItem());
		if (i < 6)
			pan[i]->setPos(57 + 8 * i, 9);
		else
			pan[i]->setPos(106, 9);

		addToGroup(pan[i]);
	}
	reset();
}

void PowerMeter::reset()
{
	
	/*for (int i = speed;i<5;i++)
	{
		pan[i]->setPixmap(texture_arrow[1]);
	}
	if(speed <7)
		pan[6]->setPixmap(texture_arrow[3]);*/

	pan[0]->setPixmap(texture_arrow[0]);
	pan[1]->setPixmap(texture_arrow[1]);
	pan[2]->setPixmap(texture_arrow[1]);
	pan[3]->setPixmap(texture_arrow[1]);
	pan[4]->setPixmap(texture_arrow[1]);
	pan[5]->setPixmap(texture_arrow[1]);
	pan[6]->setPixmap(texture_arrow[3]);
}

//void PowerMeter::decrease_speed()
//{
//	std::cout << "porcodio\n";
//	for (int i = speed; i < 5; i++)
//	{
//		pan[i]->setPixmap(texture_arrow[1]);
//	}
//	if (speed < 7)
//		pan[6]->setPixmap(texture_arrow[3]);

//}


void PowerMeter::doUpdate(const std::string& update_info)
{
	std::cout <<"prima: "<< speed << "\n";
	std::cout << update_info << "\n";
	
	speed = std::stoi(update_info);

	std::cout << "dopo: " << speed << "\n";

	if (speed == -1)
	{
		reset();
		return;
	}
	
	for (int i = 0; i <= speed; i++)					//turn on arrow
		pan[i]->setPixmap(texture_arrow[0]);

	for (int i = speed -1; i < 6; i++)					//turn of arrow
		pan[i]->setPixmap(texture_arrow[1]);

	if (speed == 7 )									//turn on P
		pan[6]->setPixmap(texture_arrow[2]);
	else											//turn off P
		pan[6]->setPixmap(texture_arrow[3]);

}
