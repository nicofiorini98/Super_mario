#include "EndLevelText.h"
#include "Sprites.h"
#include <iostream>

EndLevelText::EndLevelText(QPoint position, const std::string& text) : Inert()
{
	if (text != "CLEAR COURSE!" && text != "YOU GOT A CARD")
		std::cerr << "Text: " << "(" << text << ")" << " not valid\n"; // da rivedere

	// flags
	collidable = false;
	walkable = false;

	// texture
	texture_text = Sprites::instance()->get(text);

	setPos(position);
	setPixmap(texture_text);
}