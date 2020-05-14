#pragma once

#include "Inert.h"
#include "utility"
#include <array>
 
// NB:  ereditare da Entity
class GoalRoulette : public Inert
{
	private:

		int animation_counter;
		bool active;
		std::string content;
		std::array<std::pair<std::string ,QPixmap>,4> ranging_items;

	public:

		GoalRoulette(QPoint position);

		//getter
		std::string getContent() const { return content; }

		virtual std::string name() { return "GoalRoulette"; }
		virtual void animate();
		virtual void hit(Object* what, Direction fromDir);
};