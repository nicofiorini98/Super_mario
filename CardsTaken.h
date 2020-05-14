#pragma once

#include "NumericalPanel.h"
#include "Card.h"

class CardsTaken : public HudSubPanel
{
	private:

		std::vector<Card*>panel;

		virtual void doUpdate(const std::string& card_id);

	public:

		CardsTaken() {};

		virtual void reset();

};