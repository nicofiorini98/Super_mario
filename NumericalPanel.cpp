#include "NumericalPanel.h"
#include "Sprites.h"

NumericalPanel::NumericalPanel() : HudSubPanel()
{
	numbers[0] = Sprites::instance()->get("0");
	numbers[1] = Sprites::instance()->get("1");
	numbers[2] = Sprites::instance()->get("2");
	numbers[3] = Sprites::instance()->get("3");
	numbers[4] = Sprites::instance()->get("4");
	numbers[5] = Sprites::instance()->get("5");
	numbers[6] = Sprites::instance()->get("6");
	numbers[7] = Sprites::instance()->get("7");
	numbers[8] = Sprites::instance()->get("8");
	numbers[9] = Sprites::instance()->get("9");
}