#pragma once

#include <QPoint>
#include <QGraphicsPixmapItem>
#include <map>
#include "HudSubPanel.h"

class HudPanel : public QGraphicsPixmapItem 
{
	private:
		
		QPixmap texture_panel;
		std::map<std::string, HudSubPanel*>sub_panels;
		
	public:

		HudPanel(QPoint position);
		
		// getters
		HudSubPanel* get(const std::string& panel_id);

		void reset();
		void show();
		void updatePanel(const std::string& panel, const std::string& update_info);
};