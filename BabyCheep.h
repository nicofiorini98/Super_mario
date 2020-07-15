#pragma once
#include "Enemy.h"
#include <iostream>
class BabyCheep : public Enemy
{
    bool script_move;           //is baby launched from your mother?
    bool baby_free;             //is baby free from your mother?

	
    int script_counter;         //counts the pixel moved since the script_move is started  
    int script_duration;        //limit the frame for stay in script_move
	
    int moving_start_counter;   //counts the number of frames since the script is started

protected:

    // textures
    QPixmap texture_swim[2];		
    QPixmap texture_death;
	
public:

    BabyCheep(QPoint position, Direction direction = LEFT);

	//getter and setter
    void setScript_Move(bool _script_move, Direction _dir);
    void setBabyFree(bool _baby_free);
    bool isScript_Move() { return script_move; }
    Direction getDirection() { return dir; }

    // pure virtual methods that must be implemented
    virtual std::string name() { return "Baby_Cheep"; }
    virtual void animate();
    virtual void hit(Object* what, Direction fromDir);
    virtual void hurt();
    virtual void advance();
    

};