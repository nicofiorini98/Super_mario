#include "Score.h"
#include "Hud.h"
#include "GameTime.h"

Score::Score() : NumericalPanel()
{
	//for (int i = 0; i < 3; i++)
	//{
	//	panel_numbers.push_back(new QGraphicsPixmapItem());
	//	panel_numbers[i]->setPos(89 + 8 * i, 17);
	//	addToGroup(panel_numbers[i]);
	//}

	//units = 0;
	//dozens = 0;
	//hundreds = 0;
	//panel_numbers[0]->setPixmap(numbers[hundreds]);
	//panel_numbers[1]->setPixmap(numbers[dozens]);
	//panel_numbers[2]->setPixmap(numbers[units]);
}

void Score::doUpdate(const std::string& update_info)
{
	//if(update_info == "add-time-left")
	//	addTimeLeft();
}

void Score::reset()
{
}

void Score::addTimeLeft()
{

	//GameTime* game_time = dynamic_cast<GameTime*>(Hud::instance()->getPanel("GameTime"));
	//if (game_time)
	//{
	//	// C++17  required for the following (view CMakeLists.txt in source folder) 
	//	// REMOVE ABOVE COMMENT AFTER REFACTORING
	//	auto [time_hundreds, time_dozens, time_units] = game_time->getTimeRemaining();

	//	units += time_units;
	//	dozens += time_dozens;
	//	hundreds += time_hundreds;

	//	panel_numbers[0]->setPixmap(numbers[hundreds]);
	//	panel_numbers[1]->setPixmap(numbers[dozens]);
	//	panel_numbers[2]->setPixmap(numbers[units]);

	//}
}