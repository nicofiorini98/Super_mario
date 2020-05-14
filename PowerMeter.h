#pragma once

#include "HudSubPanel.h"


class PowerMeter : public HudSubPanel
{

	private:
		 
		virtual void doUpdate(const std::string& update_info);

	public:

		PowerMeter();

		virtual void reset();
};