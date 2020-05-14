#pragma once

#include "Inert.h"

class SwitchBlock : public Inert
{
	
	private:

		static bool switch_effect;
		int animation_counter;

		//textures
		QPixmap texture_spawning[11];
		QPixmap texture_active[3];
		QPixmap texture_smashed;
		
		bool spawning;
		bool active;

	public:

		SwitchBlock(QPoint position);

		static bool SwitchEffect() { return switch_effect; }
		virtual std::string name() { return "SwitchBlock"; }
		virtual void animate();
		virtual void hit(Object* what, Direction fromDir);
};