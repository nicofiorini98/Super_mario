#pragma once

#include "Collectable.h"

class SpinningItem : public Collectable
{
	private:

		QPixmap texture_animation[6];  // mushroom/flower/star animation textures
	
		std::string id;  // item's id                

	public:

		SpinningItem(QPoint position , const std::string& _id);

		virtual std::string name() { return "SpinningItem"; }
		virtual void advance();
		virtual void animate();
		virtual void hit(Object* what, Direction fromDir) {/* do nothing */};
};