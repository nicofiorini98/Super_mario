#pragma once

#include "NumericalPanel.h"
#include <tuple>

class GameTime : public NumericalPanel
{

	private:

		int units;
		int dozens;
		int hundreds;

		void resetValues();

		virtual void doUpdate(const std::string& update_info);

	public:

		GameTime();

		// getters
		std::tuple<int, int, int> getTimeRemaining();

		virtual void reset();

};