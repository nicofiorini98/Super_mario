#pragma once

#include "HudSubPanel.h"
//#include <QTimer>


class PowerMeter : public HudSubPanel
{
	//Q_OBJECT
	
	private:
		int power;
		virtual void doUpdate(const std::string& update_info);
		QPixmap texture_arrow[4];
		std::vector<QGraphicsPixmapItem*>pan;

	public:

		PowerMeter();

		virtual void reset();
	
};
