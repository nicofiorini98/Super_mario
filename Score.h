#pragma once

#include "NumericalPanel.h"

class Score : public NumericalPanel
{

	private:
		int units;
		int dozens;
		int hundreds;

		virtual void doUpdate(const std::string& update_info);

		void addTimeLeft();
	public:

		Score();

		virtual void reset();
};