#pragma once
#include "Enemy.h"
#include <iostream>
class BlooberBaby : public Enemy
{
    int move_id; // serve per capire quale medusa è delle 4
    bool script;
    int script_counter;
    int script_duration;
    int moving_start_counter;
    int falling_duration;
	
protected:

    // textures
    QPixmap texture_nothing;
    QPixmap texture_swim[3];		// brown/red walk animation
    QPixmap texture_death;		// brown/red smashed texture
    QPoint pos_in;
	
public:

    BlooberBaby(QPoint position, int _move_id);

    // pure virtual methods that must be implemented
    virtual std::string name() { return "Baby_Cheep";}
    virtual void animate();
    virtual void hit(Object* what, Direction fromDir){}
    virtual void hurt(){}
    virtual void advance();
    //bool get_lim() { return lim; }
    //void set_lim(bool a) { lim = a; }
    //bool get_same_pos() { return same_pos; }
    //void set_same_pos(bool a) { same_pos = a; }

    void setScript_Move(bool _script) { script = _script; }

    bool getScript_Move() { return script; }


};