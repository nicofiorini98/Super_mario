#include <QApplication>

#include <QWidget>
#include "Sprites.h"
#include "Sounds.h"
#include "Game.h"

int main(int argc, char *argv[])
{

    // create Qt application
    QApplication app(argc, argv);

	// instance sprites and sounds
	Sprites::instance();
	Sounds::instance();

	// create the game window
	QWidget* game_window = new QWidget(0);

	game_window->setFixedSize(3*16*16, 3*16*15);

	// create Super Mario game as a child of game window
	Game::instance(game_window);

	// create and set Hud's positon in game window
	Hud::instance(game_window)->move(0, 603);

	// show game_window and its contenent
	game_window->show();

	
    // launch Qt event loop
    return app.exec();
	
}