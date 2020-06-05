#pragma once

#include "HudSubPanel.h"


class PowerMeter : public HudSubPanel
{

	private:
		int speed;
		virtual void doUpdate(const std::string& update_info);
		QPixmap texture_arrow[4];
		std::vector<QGraphicsPixmapItem*>pan;

	public:

		PowerMeter();

		virtual void reset();
};