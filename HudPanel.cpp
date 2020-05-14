#include "HudPanel.h"
#include "GameTime.h"
#include "LifeCounter.h"
#include "Score.h"
#include "PowerMeter.h"
#include "CardsTaken.h"
#include "CoinCounter.h"
#include "Sprites.h"
#include "Hud.h"

HudPanel::HudPanel(QPoint position)
{

	texture_panel = Sprites::instance()->get("hud-panel");

	sub_panels["GameTime"]    = new GameTime();
	sub_panels["CardsTaken"]  = new CardsTaken();
	sub_panels["Score"]       = new Score();
	sub_panels["LifeCounter"] = new LifeCounter();
	sub_panels["CoinCounter"] = new CoinCounter();
	sub_panels["PowerMeter"]  = new PowerMeter();

	setPos(position);
	setPixmap(texture_panel);
	Hud::instance()->getScene()->addItem(this);		
}

HudSubPanel* HudPanel::get(const std::string& panel_id)
{
	if (sub_panels.find(panel_id) != sub_panels.end())
		return sub_panels[panel_id];
	else return nullptr;
}

void HudPanel::reset()
{
	this->setVisible(false);
	for (auto& sp : sub_panels)
		 sp.second->reset();
}

void HudPanel::show()
{
	this->setVisible(true);
	for (auto& sp : sub_panels)
		sp.second->setVisible(true);
}

void HudPanel::updatePanel(const std::string& panel_id, const std::string& info)
{
	if (sub_panels.find(panel_id) != sub_panels.end())
		sub_panels[panel_id]->update(info);
}