#pragma once

#include "NumericalPanel.h"


class CoinCounter : public NumericalPanel
{
	private:

		int units;
		int dozens;

		virtual void doUpdate(const std::string& update_info);

	public:

		CoinCounter();

		virtual void reset();

};