#pragma once

#include "NumericalPanel.h"

class LifeCounter : public NumericalPanel
{
	private:

		int units;
		int dozens;

		virtual void doUpdate(const std::string& update_info);
		
	public:

		LifeCounter();
		//int getLives() { return lives; }

		virtual void reset();
	
};