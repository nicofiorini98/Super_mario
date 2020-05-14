#pragma once

#include "HudSubPanel.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>

class NumericalPanel : public HudSubPanel
{
	private:

		virtual void doUpdate(const std::string& update_info) = 0;

	protected:

		QPixmap numbers[10];
		std::vector<QGraphicsPixmapItem*>panel_numbers;

	public:

		NumericalPanel();

		virtual void reset() = 0;

};