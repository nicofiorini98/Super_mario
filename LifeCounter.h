#pragma once

#include "NumericalPanel.h"

class LifeCounter : public NumericalPanel
{
	private:

		//number in panel
		int units;   
		int dozens;

		virtual void doUpdate(const std::string& update_info);
		
	public:

		LifeCounter();

		virtual void reset();
	
};