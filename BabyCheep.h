#pragma once
#include "Enemy.h"
#include <iostream>
class BabyCheep : public Enemy
{
    bool script_move;
    bool baby_free;
    int script_counter;
    int script_duration;
    int moving_start_counter;

protected:

    // textures
    QPixmap texture_swim[2];		// brown/red walk animation
    QPixmap texture_death;		// brown/red smashed texture
    QPoint pos_in;
public:

    BabyCheep(QPoint position, Direction direction = LEFT);

    // pure virtual methods that must be implemented
    virtual std::string name() { return "Baby_Cheep"; }
    virtual void animate();
    virtual void hit(Object* what, Direction fromDir);
    virtual void hurt();
    virtual void advance();
    //bool get_lim() { return lim; }
    //void set_lim(bool a) { lim = a; }
    //bool get_same_pos() { return same_pos; }
    //void set_same_pos(bool a) { same_pos = a; }
    void setScript_Move(bool _script_move, Direction _dir);
    void setBaby_free(bool _baby_free);
    bool getScript_Move() { return script_move;}
    Direction getDirection() { return dir; }

};