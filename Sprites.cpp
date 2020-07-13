#include "Sprites.h"
#include "utils.h"
#include <QBitmap>
#include <iostream>

// utility function
QRect moveBy(QRect rect, int x, int y, int dx = 16, int dy = 16, int border_x = 1, int border_y = 1)
{
	rect.moveTo(QPoint(rect.x() + x*dx + x*border_x, rect.y() + y*dy + y*border_y));
	return rect;
}

QRect moveMarioBy(QRect rect, int x, int y, int dx = 16, int dy = 16)
{
	return moveBy(rect, x, y, dx, dy, 2, 2);
}

QRect moveRight(QRect rect, int pixels)
{
	rect.translate(QPoint(pixels, 0));
	return rect;
}

// main object positions within sprites
static QRect mario_small(1, 16, 16, 16);
static QRect mario_big(1, 90, 16, 30);
static QRect mario_fire(1, 262, 16, 30);

static QRect muncher(936, 18, 16, 16);
static QRect hud_panel(3, 3, 232, 28);
static QRect pipe(1, 205, 16, 16);
static QRect mega_empty_box(835, 274, 32, 32);
static QRect coin_spawnable(290, 101, 16, 14);
static QRect coin(953, 86, 16, 16);
static QRect mushroom(156, 121, 16, 16);
static QRect ice_terrain(596, 18, 16, 16);
static QRect ice_block(528, 1, 16, 16);
static QRect sky(613,1,16,16);
static QRect night_sky(681, 188, 16, 16);
static QRect iceberg(545, 154, 16, 16);
static QRect cheep(384, 0, 16, 15);
static QRect number(33, 32, 8, 7);
static QRect downhill(0, 0, 163, 1);
static QRect wood_block(1004, 35, 16, 16);
static QRect brick_block(1038, 18, 16, 16);
static QRect broken_block(1089, 103, 8, 9);
static QRect ice_brick_block(1038, 69, 16, 16);
static QRect empty_block(1208, 1, 16, 16);
static QRect jump_block(1038, 103, 16, 16);
// "p_switch" and "switch_block" are the same object 
// (ambiguity due to object's textures location in different files within sprites)
static QRect switch_block(1174, 171, 16, 16); 
static QRect p_switch(151, 380, 16, 16);
static QRect transparent(151, 380, 19, 30);
static QRect points(82, 64, 11, 8);
static QRect roulette_item(258, 350, 16, 16);
static QRect spinning_item(258, 374, 16, 16);
static QRect firework(31, 60, 128, 128);
static QRect end_level_text(53, 365, 146, 26);
static QRect card(260, 394, 16, 16);
static QRect life_up(493, 347, 29, 16);
static QRect Koopa_Troopa(96, 51, 16, 27);
static QRect Shell(128, 48, 16, 16);
static QRect plant(0, 144, 16, 32);
static QRect plant_fire(32, 144, 16, 32);
static QRect fire_ball(245, 305, 8, 9);
static QRect boom(210, 2, 11, 11);
static QRect Splash(352, 144, 15, 15);
static QRect Bloober_Nanny(352, 160, 16, 16);
static QRect Baby_Cheep(450, 66, 12, 12);
static QRect Big_Bertha(352, 48, 24, 32);
static QRect leaf(180, 123, 16, 14);

Sprites* Sprites::instance()
{
	static Sprites uniqueInstance;
	return &uniqueInstance;
}

Sprites::Sprites()
{
	hud           = loadTexture(":/graphics/sprites/hud.png", Qt::magenta);
	mario         = loadTexture(":/graphics/sprites/mario.png", QColor(68, 145, 190));
	enemies       = loadTexture(":/graphics/sprites/enemies.png", QColor(68, 145, 190));
	stage_tiles   = loadTexture(":/graphics/sprites/stage_tiles.png");
	title_screen  = loadTexture(":/graphics/sprites/title_screen.png");
	miscs         = loadTexture(":/graphics/sprites/miscs.png", QColor(166, 185, 255));
	goal_roulette = loadTexture(":/graphics/sprites/goal_roulette.png", QColor(0, 183, 239));
	fireworks     = loadTexture(":/graphics/sprites/fireworks.png", QColor(3, 26, 110));
}

QPixmap Sprites::get(const std::string & id)
{
	if (id == "mario-small-stand")
		return mario.copy(mario_small);
	if (id == "mario-small-walk-0")
		return mario.copy(mario_small);
	if (id == "mario-small-walk-1")
		return mario.copy(moveMarioBy(mario_small, 1, 0));
    if (id == "mario-small-walk-2")
		return mario.copy(mario_small);
	if (id == "mario-small-walk-3")
		return mario.copy(moveMarioBy(mario_small, 1, 0));
	if (id == "mario-small-fall")
		return mario.copy(moveMarioBy(mario_small, 2, 0));
	if (id == "mario-small-jump")
		return mario.copy(moveMarioBy(mario_small, 2, 0));
	if (id == "mario-small-run-0")
		return mario.copy(moveMarioBy(mario_small, 3, 0));
	if (id == "mario-small-run-1")
		return mario.copy(moveMarioBy(mario_small, 4, 0));
	if (id == "mario-small-run-2")
		return mario.copy(moveMarioBy(mario_small, 3, 0));
	if (id == "mario-small-run-3")
		return mario.copy(moveMarioBy(mario_small, 4, 0));
	if (id == "mario-small-super-jump")
		return mario.copy(moveMarioBy(mario_small, 5, 0));
	if (id == "mario-small-brake")
		return mario.copy(moveMarioBy(mario_small, 6, 0));
	if (id == "mario-small-swim-0")
		return mario.copy(moveMarioBy(mario_small, 12, 0));
	if (id == "mario-small-swim-1")
		return mario.copy(moveMarioBy(mario_small, 13, 0));
	if (id == "mario-small-swim-2")
		return mario.copy(moveMarioBy(mario_small, 14, 0));
	if (id == "mario-small-swim-3")
		return mario.copy(moveMarioBy(mario_small, 15, 0));
	if (id == "mario-small-dying")
		return mario.copy(moveMarioBy(mario_small, 17, 0));
	if (id == "transparent1")
		return mario.copy(moveMarioBy(mario_small, 18, 0));
	if (id == "transparent2")
		return  miscs.copy(moveBy(transparent, 11, 0));
	
	
	if (id == "mario-big-stand")
		return mario.copy(mario_big);
	if (id == "mario-big-walk-0")
		return mario.copy(mario_big);
	if (id == "mario-big-walk-1")
		return mario.copy(moveMarioBy(mario_big, 1, 0));
	if (id == "mario-big-walk-2")
		return mario.copy(moveMarioBy(mario_big, 2, 0));
	if (id == "mario-big-walk-3")
		return mario.copy(moveMarioBy(mario_big, 1, 0));
	if (id == "mario-big-fall")
		return mario.copy(moveMarioBy(mario_big, 2, 0));
	if (id == "mario-big-jump")
		return mario.copy(moveMarioBy(mario_big, 4, 0));
	if (id == "mario-big-super-jump")
		return mario.copy(QRect(169, 90, 19, 30));
	if (id == "mario-big-run-0")
		return mario.copy(QRect(117, 90, 19, 30));
	if (id == "mario-big-run-1")
		return mario.copy(QRect(91, 90, 19, 30));
	if (id == "mario-big-run-2")
		return mario.copy(QRect(143, 90, 19, 30));
	if (id == "mario-big-run-3")
		return mario.copy(QRect(91, 90, 19, 30));
	if (id == "mario-big-brake")
		return mario.copy(QRect(195, 90, 16, 30));
	if (id == "mario-big-crouch")
		return mario.copy(QRect(55, 102, 16, 18));

	if (id == "mario-big-swim-0")
		return mario.copy(QRect(373, 93, 19, 27));
	if (id == "mario-big-swim-1")
		return mario.copy(QRect(399, 93, 19, 27));
	if (id == "mario-big-swim-2")
		return mario.copy(QRect(373, 93, 19, 27));
	if (id == "mario-big-swim-3")
		return mario.copy(QRect(347, 93, 19, 27));

	if (id == "mario-big-swim-4")
		return mario.copy(QRect(347, 93, 19, 27));
	if (id == "mario-big-swim-5")
		return mario.copy(QRect(425, 93, 19, 27));
	if (id == "mario-big-swim-6")
		return mario.copy(QRect(169, 93, 19, 27));
	
	if (id == "mario-small-pipe")
		return mario.copy(QRect(127, 16, 16, 16));
	if (id == "mario-big-pipe")
		return mario.copy(QRect(213, 91, 16, 28));
	if (id == "mario-fire-pipe")
		return mario.copy(QRect(213, 264, 16, 28));
	if (id == "mario-raccoon-pipe")
		return mario.copy(QRect(357, 350, 16, 28));
	/*if (id == "mario-raccoon-pipe")
		return mario.copy(QRect(465, 350, 19, 28));*/

	//mario trasformation
	if (id == "mario-half")
		return mario.copy(QRect(209, 132, 16, 22));

	//mario raccoon and fire transformation
	if (id == "mario-transformation-0")
		return mario.copy(QRect(451, 1, 16, 27));
	if (id == "mario-transformation-1")
		return mario.copy(QRect(469, 1, 16, 27));
	if (id == "mario-transformation-2")
		return mario.copy(QRect(415, 1, 16, 27));
	if (id == "mario-transformation-3")
		return mario.copy(QRect(433, 1, 16, 27));
	if (id == "mario-transformation-4")
		return mario.copy(QRect(469, 1, 16, 27));
	if (id == "mario-transformation-5")
		return mario.copy(QRect(451, 1, 16, 27));

	//mario fire
	if (id == "mario-fire-stand")
		return mario.copy(mario_fire);
	if (id == "mario-fire-walk-0")
		return mario.copy(mario_fire);
	if (id == "mario-fire-walk-1")
		return mario.copy(moveMarioBy(mario_fire, 1, 0));
	if (id == "mario-fire-walk-2")
		return mario.copy(moveMarioBy(mario_fire, 2, 0));
	if (id == "mario-fire-walk-3")
		return mario.copy(moveMarioBy(mario_fire, 1, 0));
	if (id == "mario-fire-fall")
		return mario.copy(moveMarioBy(mario_fire, 2, 0));
	if (id == "mario-fire-jump")
		return mario.copy(moveMarioBy(mario_fire, 4, 0));
	if (id == "mario-fire-super-jump")
		return mario.copy(QRect(169, 262, 19, 30));
	if (id == "mario-fire-run-0")
		return mario.copy(QRect(117, 262, 19, 30));
	if (id == "mario-fire-run-1")
		return mario.copy(QRect(91, 262, 19, 30));
	if (id == "mario-fire-run-2")
		return mario.copy(QRect(143, 262, 19, 30));
	if (id == "mario-fire-run-3")
		return mario.copy(QRect(91, 262, 19, 30));
	if (id == "mario-fire-brake")
		return mario.copy(QRect(195, 262, 16, 30));
	if (id == "mario-fire-crouch")
		return mario.copy(QRect(55, 274, 16, 18));
	if (id == "mario-fire-shoot-0")
		return mario.copy(QRect(209, 296, 16, 30));
	if (id == "mario-fire-shoot-1")
		return mario.copy(QRect(227, 296, 16, 30));
	
	//mario fire swim in falling
	if (id == "mario-fire-swim-0")  
		return mario.copy(QRect(373, 265, 19, 27));
	if (id == "mario-fire-swim-1")  
		return mario.copy(QRect(399, 265, 19, 27));
	if (id == "mario-fire-swim-2")  
		return mario.copy(QRect(373, 265, 19, 27));
	if (id == "mario-fire-swim-3")  
		return mario.copy(QRect(347, 265, 19, 27));
	//todo ricontrollare queste texture
	if (id == "mario-fire-swim-4") 
		return mario.copy(QRect(347, 265, 19, 27));
	if (id == "mario-fire-swim-5")  
		return mario.copy(QRect(425, 265, 19, 27));
	if (id == "mario-fire-swim-6")  
		return mario.copy(QRect(169, 265, 19, 27));


	if (id == "mario-raccoon-stand")
		return mario.copy(QRect(1, 348, 24, 30));
	if (id == "mario-raccoon-walk-0")
		return mario.copy(QRect(1, 348, 24, 30));
	if (id == "mario-raccoon-walk-1")
		return mario.copy(QRect(27, 348, 24, 30));
	if (id == "mario-raccoon-walk-2")
		return mario.copy(QRect(53, 348, 24, 30));
	if (id == "mario-raccoon-walk-3")
		return mario.copy(QRect(27, 348, 24, 30));

	if (id == "mario-raccoon-run-0")
		return mario.copy(QRect(209, 348, 24, 30));
	if (id == "mario-raccoon-run-1")
		return mario.copy(QRect(183, 348, 24, 30));
	if (id == "mario-raccoon-run-2")
		return mario.copy(QRect(235, 348, 24, 30));
	if (id == "mario-raccoon-jump")
		return mario.copy(QRect(105, 348, 24, 30));
	if (id == "mario-raccoon-crouch")
		return  mario.copy(QRect(79, 360, 24, 18));

	//todo ricontrollare
	/*if (id == "mario-raccoon-brake") 
		return mario.copy(QRect(439, 348, 24, 30));*/
	if (id == "mario-raccoon-brake") 
		return mario.copy(QRect(439, 312, 24, 30));

	//different fall foor mario raccoon
	if (id == "mario-raccoon-fall-0")
		return mario.copy(QRect(131, 348, 24, 30));
	if (id == "mario-raccoon-fall-1")
		return mario.copy(QRect(157, 348, 24, 30));
	if (id == "mario-raccoon-fall-2")
		return mario.copy(QRect(53, 348, 24, 30));

	//mario fly
	if (id == "mario-raccoon-fly-0")
		return mario.copy(QRect(261, 348, 24, 30));
	if (id == "mario-raccoon-fly-1")
		return mario.copy(QRect(313, 348, 24, 30));
	if (id == "mario-raccoon-fly-2")
		return mario.copy(QRect(287, 348, 24, 30));

	//mario tail hit
	if (id == "mario-raccoon-tail-attack-0")
		return mario.copy(QRect(375, 348, 24, 30)); 
	if (id == "mario-raccoon-tail-attack-1")
		return mario.copy(QRect(465, 348, 24, 30));
	if (id == "mario-raccoon-tail-attack-2")
		return mario.copy(QRect(375, 348, 24, 30));
	if (id == "mario-raccoon-tail-attack-3")
		return mario.copy(QRect(401, 348, 24, 30));
	if (id == "mario-raccoon-tail-attack-4")
		return mario.copy(QRect(375, 348, 24, 30));

	if (id == "mario-raccoon-swim-0")
		return mario.copy(QRect(149, 384, 24, 28)); 
	if (id == "mario-raccoon-swim-1")
		return mario.copy(QRect(175, 384, 24, 28));
	if (id == "mario-raccoon-swim-2")
		return mario.copy(QRect(149, 384, 24, 28));
	if (id == "mario-raccoon-swim-3")
		return mario.copy(QRect(123, 384, 24, 28));
	//sequenza mario swimming
	if (id == "mario-raccoon-swim-4")
		return mario.copy(QRect(149, 384, 24, 28));
	if (id == "mario-raccoon-swim-5")
		return mario.copy(QRect(201, 384, 24, 28));
	if (id == "mario-raccoon-swim-6")
		return mario.copy(QRect(287, 350, 24, 28));
	
	if (id == "ice-terrain-L")
		return stage_tiles.copy(ice_terrain);
	if (id == "ice-terrain-C")
		return stage_tiles.copy(moveBy(ice_terrain, 1, 0));
	if (id == "ice-terrain-R")
		return stage_tiles.copy(moveBy(ice_terrain, 2, 0));

	if (id == "ice-block-NW")
		return stage_tiles.copy(ice_block);
	if (id == "ice-block-NE")
		return stage_tiles.copy(moveBy(ice_block, 1, 0));
	if (id == "ice-block-SW")
		return stage_tiles.copy(moveBy(ice_block, 0, 1));
	if (id == "ice-block-SE")
		return stage_tiles.copy(moveBy(ice_block, 1, 1));

	if (id == "wood-block")
		return stage_tiles.copy(wood_block);

	if (id == "Iceberg1-NW")
		return stage_tiles.copy(iceberg);
	if (id == "Iceberg1-N")
		return stage_tiles.copy(moveBy(iceberg, 1, 0));
	if (id == "Iceberg1-NE")
		return stage_tiles.copy(moveBy(iceberg, 2, 0));
	if (id == "Iceberg1-W")
		return stage_tiles.copy(moveBy(iceberg, 0, 1));
	if (id == "Iceberg1-C")
		return stage_tiles.copy(moveBy(iceberg, 1, 1));
	if (id == "Iceberg1-E")
		return stage_tiles.copy(moveBy(iceberg, 2, 1));
	if (id == "Iceberg1-SW")
		return stage_tiles.copy(moveBy(iceberg, 0, 2));
	if (id == "Iceberg1-S")
		return stage_tiles.copy(moveBy(iceberg, 1, 2));
	if (id == "Iceberg1-SE")
		return stage_tiles.copy(moveBy(iceberg, 2, 2));

	if (id == "underwaterIceberg1-NW")
		return stage_tiles.copy(moveBy(iceberg,-3, 3));
	if (id == "underwaterIceberg1-N")
		return stage_tiles.copy(moveBy(iceberg,-2, 3));
	if (id == "underwaterIceberg1-NE")
		return stage_tiles.copy(moveBy(iceberg,-1, 3));
	if (id == "underwaterIceberg1-W")
		return stage_tiles.copy(moveBy(iceberg,-3, 4));
	if (id == "underwaterIceberg1-C")
		return stage_tiles.copy(moveBy(iceberg,-2, 4));
	if (id == "underwaterIceberg1-E")
		return stage_tiles.copy(moveBy(iceberg,-1, 4));
	if (id == "underwaterIceberg1-SW")
		return stage_tiles.copy(moveBy(iceberg,-3, 5));
	if (id == "underwaterIceberg1-S")
		return stage_tiles.copy(moveBy(iceberg,-2, 5));
	if (id == "underwaterIceberg1-SE")
		return stage_tiles.copy(moveBy(iceberg,-1, 5));
	
	if (id == "Iceberg2-NW")
		return stage_tiles.copy(moveBy(iceberg, 0, 3));
	if (id == "Iceberg2-N")
		return stage_tiles.copy(moveBy(iceberg, 1, 3));
	if (id == "Iceberg2-NE")
		return stage_tiles.copy(moveBy(iceberg, 2, 3));
	if (id == "Iceberg2-W")
		return stage_tiles.copy(moveBy(iceberg, 0, 4));
	if (id == "Iceberg2-C")
		return stage_tiles.copy(moveBy(iceberg, 1, 4));
	if (id == "Iceberg2-E")
		return stage_tiles.copy(moveBy(iceberg, 2, 4));
	if (id == "Iceberg2-SW")
		return stage_tiles.copy(moveBy(iceberg, 0, 5));
	if (id == "Iceberg2-S")
		return stage_tiles.copy(moveBy(iceberg, 1, 5));
	if (id == "Iceberg2-SE")
		return stage_tiles.copy(moveBy(iceberg, 2, 5));

	if (id == "underwaterIceberg2-N")
		return stage_tiles.copy(moveBy(iceberg, 4, 5));

	if (id == "downhill")
		return hud.copy(downhill);
	if (id == "downhill2")
		return hud.copy(downhill);
	if (id == "uphill")
		return hud.copy(downhill);
	if(id=="ice")
		return hud.copy(downhill);

	if (id == "main-screen")
		return title_screen.copy(QRect(516, 226, 16*16, 15*16));
	if (id == "hud-main-screen")
		return title_screen.copy(QRect(516, 428, 16 * 16, 16));

	if (id == "hud-panel")
		return hud.copy(hud_panel);
	if (id == "0")
		return hud.copy(number);
	if (id == "1")
		return hud.copy(moveRight(number, 10));
	if (id == "2")
		return hud.copy(moveRight(number, 20));
	if (id == "3")
		return hud.copy(moveRight(number, 30));
	if (id == "4")
		return hud.copy(moveRight(number, 40));
	if (id == "5")
		return hud.copy(moveRight(number, 50));
	if (id == "6")
		return hud.copy(moveRight(number, 60));
	if (id == "7")
		return hud.copy(moveRight(number, 70));
	if (id == "8")
		return hud.copy(moveRight(number, 80));
	if (id == "9")
		return hud.copy(moveRight(number, 90));
	if (id == "arrow")
		return hud.copy(QRect(3, 33, 8, 7));
	if (id == "P")
		return hud.copy(QRect(12, 33, 15, 7));
	if (id == "arrow-transparent")
		return hud.copy(QRect(240,3, 8, 7));
	if (id == "P-transparent")
		return hud.copy(QRect(240,3, 15, 7));


	//Score Spawnable
	if (id == "100")
		return hud.copy(QRect(82,64, 11, 8));
	if (id == "200")
		return hud.copy(QRect(96,64, 12, 8));
	if (id == "400")
		return hud.copy(QRect(111, 64, 12, 8));
	if (id == "800")
		return hud.copy(QRect(126, 64, 12, 8));
	if (id == "1000")
		return hud.copy(QRect(141, 64, 15, 8));
	if (id == "2000")
		return hud.copy(QRect(159, 64, 16, 8));
	if (id == "4000")
		return hud.copy(QRect(178, 64, 16, 8));
	if (id == "8000")
		return hud.copy(QRect(197, 64, 16, 8));
	if (id == "1up")
		return hud.copy(QRect(216, 64, 16, 8));
	
	

	if (id == "pipe1-NW")
		return stage_tiles.copy(moveBy(pipe, 0, 0));
	if (id == "pipe1-NE")
		return stage_tiles.copy(moveBy(pipe, 1, 0));
	if (id == "pipe1-W")
		return stage_tiles.copy(moveBy(pipe, 0, 1));
	if (id == "pipe1-E")
		return stage_tiles.copy(moveBy(pipe, 1, 1));
	
	if (id == "pipe2-NW")
	 	return stage_tiles.copy(moveBy(pipe, 4, 0));
	if (id == "pipe2-NE")
		return stage_tiles.copy(moveBy(pipe, 5, 0));
	if (id == "pipe2-W")
		return stage_tiles.copy(moveBy(pipe, 4, 1));
	if (id == "pipe2-E")
		return stage_tiles.copy(moveBy(pipe, 5, 1));
	if (id == "rotatedpipe2-NW")
		return stage_tiles.copy(moveBy(pipe, 6, 0));
	if (id == "rotatedpipe2-NE")
		return stage_tiles.copy(moveBy(pipe, 7, 0));
	if (id == "rotatedpipe2-W")
		return stage_tiles.copy(moveBy(pipe, 6, 1));
	if (id == "rotatedpipe2-E")
		return stage_tiles.copy(moveBy(pipe, 7, 1));

	if (id == "pipe3-NW")
		return stage_tiles.copy(moveBy(pipe, 4, -8));
	if (id == "pipe3-NE")
		return stage_tiles.copy(moveBy(pipe, 5, -8));
	if (id == "pipe3-W")
		return stage_tiles.copy(moveBy(pipe, 4, -7));
	if (id == "pipe3-E")
		return stage_tiles.copy(moveBy(pipe, 5, -7));
	if (id == "rotatedpipe3-NW")
		return stage_tiles.copy(moveBy(pipe, 6, -8));
	if (id == "rotatedpipe3-NE")
		return stage_tiles.copy(moveBy(pipe, 7, -8));
	if (id == "rotatedpipe3-W")
		return stage_tiles.copy(moveBy(pipe, 6, -7));
	if (id == "rotatedpipe3-E")
		return stage_tiles.copy(moveBy(pipe, 7, -7));

	if (id == "coin-0")
		return stage_tiles.copy(coin);
	if (id == "coin-1")
		return stage_tiles.copy(moveBy(coin, 1, 0));
	if (id == "coin-2")
		return stage_tiles.copy(moveBy(coin, 2, 0));
	if (id == "coin-3")
		return stage_tiles.copy(moveBy(coin, 4, 0));
	if (id == "coin-spawnable-0")
		return miscs.copy(coin_spawnable);
	if (id == "coin-spawnable-1")
		return miscs.copy(moveRight(coin_spawnable, 24));
	if(id == "coin-spawnable-2")
		return miscs.copy(moveRight(coin_spawnable, 13));

	if (id == "mushroom-red")
		return miscs.copy(mushroom);
	if (id == "mushroom-green")
		return miscs.copy(moveRight(mushroom, 130));
	if (id == "flower")
		return miscs.copy(QRect(309, 121, 16,16));
	
	//enemies
	if (id == "cheep-0")
		return enemies.copy(cheep);
	if (id == "cheep-1")
		return enemies.copy(moveBy(cheep,1,0,16,16,0,0));
	
	
	if (id == "big-bertha-0")
		return enemies.copy(Big_Bertha);
	if (id == "big-bertha-1")
		return enemies.copy(moveBy(Big_Bertha, 1, 0, 24, 32, 0, 0));
	if (id == "big-bertha-2")
		return enemies.copy(moveBy(Big_Bertha, 2, 0, 24, 32, 0, 0));
	if (id == "big-bertha-3")
		return enemies.copy(moveBy(Big_Bertha, 3, 0, 24, 32, 0, 0));
	if (id == "baby-cheep-0")
		return enemies.copy(QRect(450, 66, 12, 12));
	if (id == "baby-cheep-1")
		return enemies.copy(QRect(466, 66, 12, 12));
	
	if (id == "Bloober-Nanny-0")
		return enemies.copy(Bloober_Nanny);
	if (id == "Bloober-Nanny-1")
		return enemies.copy(moveBy(Bloober_Nanny, 1, 0, 16, 0, 0, 0));
	if (id == "Bloober-Nanny-2") //bloober attack, yellow texture
		return enemies.copy(QRect(482, 160, 16, 16));
	if (id == "Bloober-Baby-0")
		return enemies.copy(QRect(388, 163, 8, 10));
	if (id == "Bloober-Baby-1")
		return enemies.copy(QRect(404, 163, 8, 10));
	if (id == "Bloober-Baby-2")
		return enemies.copy(QRect(500, 163, 8, 10)); //babie attack, yellow texture

	 //tartaruga
	if (id == "Koopa_Troopa-0")
		return enemies.copy(Koopa_Troopa);
	if (id == "Koopa_Troopa-1")
		return enemies.copy(moveBy(Koopa_Troopa, 1, 0, 16, 27, 0, 0));
	if (id == "Shell-moving-0")
		return enemies.copy(Shell);
	if (id == "Shell-moving-1")
		return enemies.copy(moveBy(Shell, 1, 0, 16, 17, 0, 0));
	if (id == "Shell-moving-2")
		return enemies.copy(moveBy(Shell, 2, 0, 16, 17, 0, 0));
	if (id == "Shell-moving-3")
		return enemies.copy(moveBy(Shell, 3, 0, 16, 17, 0, 0));
	if (id == "Blocked-Shell")
		return enemies.copy(moveBy(Shell, 0, 1, 16, 16, 0, 0));


	if (id == "Splash-0")  
		return enemies.copy(Splash);
	if (id == "Splash-1")
		return enemies.copy(moveBy(Splash, 1, 0, 16, 0, 0, 0));
	if (id == "Splash-2")
		return enemies.copy(moveBy(Splash, 2, 0, 16, 0, 0, 0));
	if (id == "Splash-3")
		return enemies.copy(moveBy(Splash, 3, 0, 16, 0, 0, 0));
	if (id == "Splash-4")
		return enemies.copy(moveBy(Splash, 4, 0, 16, 0, 0, 0));

	
	if (id == "green-plant-0")
		return enemies.copy(plant);
	if (id == "green-plant-1")
		return enemies.copy(moveBy(plant, 1, 0, 16, 16, 0, 0));
	if (id == "red-plant-0")
		return enemies.copy(moveBy(plant, 6, 0, 16, 16, 0, 0));
	if (id == "red-plant-1")
		return enemies.copy(moveBy(plant, 7, 0, 16, 16, 0, 0));
	if (id == "plant-fire-down-0")
		return enemies.copy(plant_fire);
	if (id == "plant-fire-down-1")
		return enemies.copy(moveBy(plant_fire, 1, 0, 16, 16, 0, 0));
	if (id == "plant-fire-up-0")
		return enemies.copy(moveBy(plant_fire, 2, 0, 16, 16, 0, 0));
	if (id == "plant-fire-up-1")
		return enemies.copy(moveBy(plant_fire, 3, 0, 16, 16, 0, 0));

	if (id == "piranha-dying-0")
		return enemies.copy(QRect(192, 0, 16, 16));
	if (id == "piranha-dying-1")
		return enemies.copy(QRect(192, 16, 16, 16));
	if (id == "piranha-dying-2")
		return enemies.copy(QRect(224, 0, 16, 16));
	if (id == "piranha-dying-3")
		return enemies.copy(QRect(224, 16, 16, 16));
	if (id == "piranha-dying-4")
		return enemies.copy(QRect(240, 0, 16, 16));
	if (id == "piranha-dying-5")
		return enemies.copy(QRect(240, 16, 16, 16));

	if (id == "fire-ball-left-0")
		return mario.copy(fire_ball);
	if (id == "fire-ball-left-1")
		return mario.copy(moveBy(fire_ball, 1, 0, 10, 10, 0, 0));
	if (id == "fire-ball-left-2")
		return mario.copy(moveBy(fire_ball, 2, 0, 10, 10, 0, 0));
	if (id == "fire-ball-left-3")
		return mario.copy(moveBy(fire_ball, 3, 0, 10, 10, 0, 0));

	if (id == "boom-0")
		return enemies.copy(boom);
	if (id == "boom-1")
		return enemies.copy(moveBy(boom, 1, 0, 16, 11, 0, 0));
	if (id == "boom-2")
		return enemies.copy(moveBy(boom, 2, 0, 16, 11, 0, 0));
	
	 if (id == "leaf")
		 return miscs.copy(leaf);
	
	if (id == "muncher-0")
		return stage_tiles.copy(muncher);
	if (id == "muncher-1")
		return stage_tiles.copy(moveBy(muncher, 1, 0));
	if (id == "muncher-2")
		return stage_tiles.copy(moveBy(muncher, 2, 0));

	if (id == "empty-block")
		return stage_tiles.copy(empty_block);
	if (id == "red-empty-block")
		return stage_tiles.copy(moveBy(empty_block, 0, 1));
	if (id == "mega-empty-box")

		return stage_tiles.copy(mega_empty_box);
	if (id == "mega-secret-box")
		return stage_tiles.copy(moveBy(mega_empty_box, 1, 0,32));
	
	if (id == "brick-block-0")
		return stage_tiles.copy(brick_block);
	if (id == "brick-block-1")
		return stage_tiles.copy(moveBy(brick_block, 1, 0));
	if (id == "brick-block-2")
		return stage_tiles.copy(moveBy(brick_block, 2, 0));
	if (id == "brick-block-3")
		return stage_tiles.copy(moveBy(brick_block, 3, 0));
	
	if (id == "ice-brick-block-0")
		return stage_tiles.copy(ice_brick_block);
	if (id == "ice-brick-block-1")
		return stage_tiles.copy(moveBy(ice_brick_block, 1, 0));
	if (id == "ice-brick-block-2")
		return stage_tiles.copy(moveBy(ice_brick_block, 2, 0));
	if (id == "ice-brick-block-3")
		return stage_tiles.copy(moveBy(ice_brick_block, 2, 0));
	if (id == "jump-block-0")
		return stage_tiles.copy(jump_block);
	if (id == "jump-block-1")
		return stage_tiles.copy(moveBy(jump_block, 1, 0));
	if (id == "jump-block-2")
		return stage_tiles.copy(moveBy(jump_block, 2, 0));
	//frammenti di blocco
	if (id == "broken-block")
		return stage_tiles.copy(broken_block);
	
	if (id == "switch-block-0")
		return miscs.copy(p_switch);
	if (id == "switch-block-1")
		return miscs.copy(moveBy(p_switch, 1, 0));
	if (id == "switch-block-2")
		return miscs.copy(moveBy(p_switch, 2, 0));
	if (id == "switch-block-3")
		return miscs.copy(moveBy(p_switch, 3, 0));
	if (id == "switch-block-4")
		return miscs.copy(moveBy(p_switch, 4, 0));
	if (id == "switch-block-5")
		return miscs.copy(moveBy(p_switch, 5, 0));
	if (id == "switch-block-6")
		return miscs.copy(moveBy(p_switch, 6, 0));
	if (id == "switch-block-7")
		return miscs.copy(moveBy(p_switch, 7, 0));
	if (id == "switch-block-8")
		return miscs.copy(moveBy(p_switch, 8, 0));
	if (id == "switch-block-9")
		return miscs.copy(moveBy(p_switch, 9, 0));
	if (id == "switch-block-10")
		return miscs.copy(moveBy(p_switch, 10, 0));
	if (id == "switch-block-11")
		return stage_tiles.copy(switch_block);
	if (id == "switch-block-12")
		return stage_tiles.copy(moveBy(switch_block, 1, 0));
	if (id == "switch-block-13")
		return stage_tiles.copy(moveBy(switch_block, 2, 0));
	if (id == "switch-block-smashed")
		return stage_tiles.copy(moveBy(switch_block, 3, 0));
	
	if (id == "sky")
		return stage_tiles.copy(sky);
	if (id == "night-sky")
		return stage_tiles.copy(night_sky);
	if (id == "night-sky2")
		return stage_tiles.copy(moveBy(night_sky, 0, 3));

	if (id == "transparent-block")
		return  miscs.copy(moveBy(p_switch, 11, 0));

	if (id == "star-item")
		return goal_roulette.copy(roulette_item);
	if (id == "flower-item")
		return goal_roulette.copy(moveRight(roulette_item, 20));
	if (id == "mushroom-item")
		return goal_roulette.copy(moveRight(roulette_item, 40));
	if( id == "no-item")
		return goal_roulette.copy(moveRight(roulette_item, 57));

	if (id == "spinning-mushroom-1")
		return goal_roulette.copy(spinning_item);
	if (id == "spinning-flower-1")
		return goal_roulette.copy(moveBy(spinning_item, 1, 0));
	if (id == "spinning-star-1")
		return goal_roulette.copy(moveBy(spinning_item, 2, 0));
	if (id == "spinning-mushroom-2")
		return goal_roulette.copy(moveBy(spinning_item, 3, 0));
	if (id == "spinning-flower-2")
		return goal_roulette.copy(moveBy(spinning_item, 4, 0));
	if (id == "spinning-star-2")
		return goal_roulette.copy(moveBy(spinning_item, 5, 0));
	if (id == "spinning-item-3")
		return goal_roulette.copy(moveBy(spinning_item, 6, 0));
	if (id == "spinning-item-4")
		return goal_roulette.copy(moveBy(spinning_item, 7, 0));
	if (id == "spinning-item-5")
		return goal_roulette.copy(moveBy(spinning_item, 8, 0));
	if (id == "spinning-item-6")
		return goal_roulette.copy(moveBy(spinning_item, 9, 0));

	//if (id == "100")
	//	return hud.copy(points);
	//if (id == "200")
	//	return hud.copy(moveRight(point, ));
	//if (id == "400")
	//	return hud.copy(moveRight(point, ));
	//if (id == "800")
	//	return hud.copy(moveRight(point, ));
	//if (id == "1000")
	//	return hud.copy(moveRight(point, ));
	//if (id == "2000")
	//	return hud.copy(moveRight(point, ));
	//if (id == "4000")
	//	return hud.copy(moveRight(point, ));
	//if (id == "8000")
	//	return hud.copy(moveRight(point, ));

	if (id == "mushroom-firework-1")
		return fireworks.copy(firework);
	if (id == "mushroom-firework-2")
		return fireworks.copy(moveBy(firework, 1, 0, 128, 0, 19, 0));
	if (id == "mushroom-firework-3")
		return fireworks.copy(moveBy(firework, 2, 0, 128, 0, 19, 0));
	if (id == "flower-firework-1")
		return fireworks.copy(moveBy(firework, 0, 1, 0, 128, 0, 25));
	if (id == "flower-firework-2")
		return fireworks.copy(moveBy(firework, 1, 1, 128, 128, 19, 25));
	if (id == "flower-firework-3")
		return fireworks.copy(moveBy(firework, 2, 1, 128, 128, 19, 25));
	if (id == "star-firework-1")
		return fireworks.copy(moveBy(firework, 0, 2, 0, 128, 0, 25));
	if (id == "star-firework-2")
		return fireworks.copy(moveBy(firework, 1, 2, 128, 128, 19, 25));
	if (id == "star-firework-3")
		return fireworks.copy(moveBy(firework, 2, 2, 128, 128, 19, 25));

	if (id == "flower-card")
		return goal_roulette.copy(card);
	if (id == "mushroom-card")
		return goal_roulette.copy(moveRight(card, 18));
	if (id == "star-card")
		return goal_roulette.copy(moveRight(card, 36));

	if (id == "CLEAR COURSE!")
		return goal_roulette.copy(end_level_text);
	if (id == "YOU GOT A CARD")
		return goal_roulette.copy(moveBy(end_level_text, 0, 1, 0, 26));

	if (id == "1-Up")
		return goal_roulette.copy(life_up);
	if (id == "2-Up")
		return goal_roulette.copy(moveBy(life_up, 0, 1));
	if (id == "3-Up")
		return goal_roulette.copy(moveBy(life_up, 0, 2));
	if (id == "5-Up")
		return goal_roulette.copy(moveBy(life_up, 0, 3));

	
	return QPixmap();
}