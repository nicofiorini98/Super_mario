#pragma once

#include <QPixmap>

// Singleton class
class Sprites
{
	private:

		// sprites
		QPixmap hud;
		QPixmap enemies;
		QPixmap mario;
		QPixmap transparency;
		QPixmap stage_tiles;
		QPixmap title_screen;
		QPixmap miscs;
		QPixmap goal_roulette;
		QPixmap fireworks;
		
		Sprites();

	public:

		// singleton
		static Sprites* instance();

		// extract texture from sprites using the given id
		QPixmap get(const std::string & id);
};