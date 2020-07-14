#include "CardsTaken.h"
#include "Hud.h"
#include "Game.h"

void CardsTaken::reset()
{
	//clears panel if is full

	if (!panel.empty())
	{
		if (panel.size() == 3)
		{
			for (auto& card : panel)
				delete card;

			panel.clear();
		}

		HudSubPanel::reset();
	}
}

void CardsTaken::doUpdate(const std::string& card_id)
{
	//adds card for each free slot

	if (panel.empty())
	{
		panel.push_back(new Card(QPoint(169, 8), card_id, Hud::instance()->getScene()));
		addToGroup(panel[0]);
	}
	else if (panel.size() == 1)
	{
		panel.push_back(new Card(QPoint(193, 8), card_id, Hud::instance()->getScene()));
		addToGroup(panel[1]);
	}
	else if (panel.size() == 2)
	{
		panel.push_back(new Card(QPoint(218, 8), card_id, Hud::instance()->getScene()));
		addToGroup(panel[2]);
		
	}
}