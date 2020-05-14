#include "CoinCounter.h"
#include "Hud.h"

CoinCounter::CoinCounter() 
{

	for (int i = 0; i < 2; i++)
	{
		panel_numbers.push_back(new QGraphicsPixmapItem());
		panel_numbers[i]->setPos(137 + 8*i, 9);
		addToGroup(panel_numbers[i]);
	}

	units = 0;
	dozens = 0;
	panel_numbers[0]->setPixmap(numbers[dozens]);
	panel_numbers[1]->setPixmap(numbers[units]);
}

void CoinCounter::doUpdate(const std::string& update_info)
{

	if (units == 9 && dozens == 9)
	{
		dozens = 0;
		units = 1;
		panel_numbers[1]->setPixmap(numbers[units]);
		panel_numbers[0]->setPixmap(numbers[dozens]);
	}
	else if (units == 9)
	{
		units = 0;
		panel_numbers[1]->setPixmap(numbers[units]);
		panel_numbers[0]->setPixmap(numbers[++dozens]);
	}
	else
		panel_numbers[1]->setPixmap(numbers[++units]);
}

void CoinCounter::reset()
{
	HudSubPanel::reset();
}