#include "LifeCounter.h"

LifeCounter::LifeCounter() :NumericalPanel()
{
	units = 4;
	dozens = 0;
	
	for (int i = 0; i < 2; i++)
	{
		panel_numbers.push_back(new QGraphicsPixmapItem());
		panel_numbers[i]->setPos(34 + 8 * i, 17);
		addToGroup(panel_numbers[i]);
	}

	
	panel_numbers[0]->setPixmap(numbers[dozens]);
	panel_numbers[1]->setPixmap(numbers[units]);
}

void LifeCounter::reset()
{
	units = 4;
	dozens = 0;
	HudSubPanel::reset();
	
}

void LifeCounter::doUpdate(const std::string& update_info)
{
	int info = std::stoi(update_info);
	

	dozens = info / 10;
	info = info % 10;

	units = info;
	
	panel_numbers[0]->setPixmap(numbers[dozens]);
	panel_numbers[1]->setPixmap(numbers[units]);
}