#pragma once

#include <QGraphicsView>
#include "HudPanel.h"

class Hud : public QGraphicsView
{
	Q_OBJECT
	private:

		static Hud* uniqueInstance;	// Singleton design pattern
		Hud(QWidget* parent = nullptr);	// Singleton design pattern


		QGraphicsScene* scene;            // the scene used to render the hud 
		QGraphicsPixmapItem* main_screen; // the image displayed when game is resetted
		HudPanel* hud_panel;              // the panel containing others subpanels (i.e. score, time_remaining, etc..)

	public:
		// singleton unique instance getter
		static Hud* instance(QWidget* parent = nullptr);

		// getters
		QGraphicsScene* getScene()  { return scene; }
		HudSubPanel* getPanel(const std::string& panel_id);

	public slots:

		void start();

		void reset();

		void updatePanel(const std::string& panel_id, const std::string& update_info = "");

};