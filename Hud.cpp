#include <QGraphicsPixmapItem>
#include "Sprites.h"
#include "Hud.h"
#include "Game.h"

// Singleton design pattern
Hud* Hud::uniqueInstance = nullptr;
Hud* Hud::instance(QWidget* parent)
{
	if (uniqueInstance == nullptr)
		uniqueInstance = new Hud(parent);
	return uniqueInstance;
}

Hud::Hud(QWidget* parent) : QGraphicsView(parent)
{

	// setup scene/view
	scene = new QGraphicsScene();
	scene->setBackgroundBrush(QBrush(Qt::black));
	setScene(scene);
	
	setFixedSize(3*16*16 , 3*39);

	scale(3.0, 3.0);

	scene->setSceneRect(0, 0, 16*16, 39);

	setFrameShape(QFrame::NoFrame);
	setInteractive(false);		// disables events
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	// initially only main screen is displayed 
	hud_panel = nullptr;
	
	main_screen = new QGraphicsPixmapItem(Sprites::instance()->get("hud-main-screen"));
	scene->addItem(main_screen);


	// setup game timer
	connect(Game::instance()->gameTime(), &QTimer::timeout, this, [this] {(updatePanel("GameTime")); });
	
}

// rename properly this function
void Hud::start()
{
	if (!hud_panel)
		hud_panel = new HudPanel(QPoint(5, 2));
	
	main_screen->setVisible(false);
	hud_panel->show();
}

void Hud::reset()
{
	if(hud_panel)
		hud_panel->reset();
	main_screen->setVisible(true);
}

void Hud::updatePanel(const std::string& panel_id, const std::string& info)
{
	hud_panel->updatePanel(panel_id, info);
}

HudSubPanel* Hud::getPanel(const std::string& panel_id)
{
	if (hud_panel->get(panel_id))
		return hud_panel->get(panel_id);
	else 
		return nullptr;
}