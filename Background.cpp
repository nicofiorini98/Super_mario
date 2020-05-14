#include "Background.h"
#include "Sprites.h"
#include <QPainter>

Background::Background()
{
	collidable = false;
}

Background::Background(QPoint position, std::string _texture_path)
{
	// all background objects are not collidable
	collidable = false;

	// load texture
	texture_path = _texture_path;
	setPixmap(loadTexture(texture_path));

	// correct y-coordinate w.r.t. texture height
	setPos(position-QPoint(0, pixmap().height()));
}

Background::Background(QPoint position, QPixmap pix)
{
	// all background objects are not collidable
	collidable = false;

	// make background color (224, 163, 216) transparent
	pix.setMask(pix.createMaskFromColor(QColor(224, 163, 216)));

	// load texture
	setPixmap(pix);

	// correct y-coordinate w.r.t. texture height
	setPos(position-QPoint(0, pixmap().height()));
}