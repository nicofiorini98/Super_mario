#include "HudSubPanel.h"
#include "Hud.h"

HudSubPanel::HudSubPanel()
{
	
	
	Hud::instance()->getScene()->addItem(this);
	setZValue(2);
}

void HudSubPanel::reset()
{
    setVisible(false);
}