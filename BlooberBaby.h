#pragma once
#include "Enemy.h"
#include <iostream>
class BlooberBaby : public Enemy
{
    int move_id; // each son is enumerated
    bool script;   //is blooberbaby freed?

    //counts the number of frame during moving phase
    int script_counter;  
    int moving_start_counter;
    
    //physical parameter when is freed
    int script_duration;
    int falling_duration;
	
protected:

    // textures
    QPixmap texture_nothing;
    QPixmap texture_swim[3];		
    QPixmap texture_death;		
    QPoint pos_in;
	
public:

    BlooberBaby(QPoint position, int _move_id);

    // pure virtual methods that must be implemented
    virtual std::string name() { return "Baby_Cheep";}
    virtual void animate();
    virtual void hit(Object* what, Direction fromDir);
    virtual void hurt(){}
    virtual void advance();
	
    void setScript_Move(bool _script) { script = _script; }
    void setDying(bool _dying) { dying = _dying;}
    bool getScript_Move() { return script; }


};