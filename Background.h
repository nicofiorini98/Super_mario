#pragma once

#include "Inert.h"

// Background objects
class Background : public Inert
{
	protected:

		std::string texture_path;

	public:

		Background();
		Background(QPoint position, std::string _texture_path);
		Background(QPoint position, QPixmap pixmap);
		
		// inherited methods
		virtual std::string name() {return std::string("Background (") + texture_path + ")";}
		virtual void hit(Object *what, Direction fromDir) { /* do nothing */ };
};