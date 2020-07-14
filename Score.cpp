#include "Score.h"
#include "Hud.h"
#include "GameTime.h"
#include <iostream>

Score::Score() : NumericalPanel()
{
	units =0;
	dozens =0;
	hundreds =0;
	thousands =0;
	ten_thousands=0;
	hundreds_thousands=0;
	millions =0;

	for (int i = 0; i < 7; i++)
	{
		panel_numbers.push_back(new QGraphicsPixmapItem());
		panel_numbers[i]->setPos(57 + 8 * i, 17);
		addToGroup(panel_numbers[i]);
	}
	
	drawScore();
}

void Score::doUpdate(const std::string& update_info)
{
	
	int info = std::stoi(update_info);

	millions = info / 1000000;
	info = info % 1000000;

	hundreds_thousands = info / 100000;
	info = info % 100000;

	ten_thousands = info / 10000;
	info = info % 10000;

	thousands = info / 1000;
	info = info % 1000;
	
	hundreds = info / 100;
	info = info % 100;
	
	dozens = info / 10;
	info = info % 10;
	
	units = info;

	drawScore();
}

void Score::drawScore()
{
	panel_numbers[0]->setPixmap(numbers[millions]);
	panel_numbers[1]->setPixmap(numbers[hundreds_thousands]);
	panel_numbers[2]->setPixmap(numbers[ten_thousands]);
	panel_numbers[3]->setPixmap(numbers[thousands]);
	panel_numbers[4]->setPixmap(numbers[hundreds]);
	panel_numbers[5]->setPixmap(numbers[dozens]);
	panel_numbers[6]->setPixmap(numbers[units]);
}

void Score::reset()
{
	units = 0;
	dozens = 0;
	hundreds = 0;
	thousands = 0;
	ten_thousands = 0;
	hundreds_thousands = 0;
	millions = 0;
	
	drawScore();

	
		
	HudSubPanel::reset();
	
}
