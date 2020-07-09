#pragma once
#include "Enemy.h"
#include "Mario.h"
#include "BlooberBaby.h"
#include "array"


class BlooberNanny : public Enemy
{

protected:

    Mario* mario;

	//pointer to own babies
    BlooberBaby* baby1;
    BlooberBaby* baby2;
    BlooberBaby* baby3;
    BlooberBaby* baby4;
    
    //memorize 40 previous positions
    int previous_pos;          
    std::array<QPoint,40> nframe_prev_pos;
	
	//flag for identified the script to do
    bool over_head;
    bool near_head;
    bool under_head;

	//flag collision detection 
    bool blocked_up;
    bool blocked_side;
    bool blocked_down;

    bool splash;
    bool first;

    bool spawn_baby; //mi serve per gestire il lancio degli uttri, non dovrebbe servire più, faccio una cosa analoga di Big_Bertha
    int spawn_counter;
    int spawn_duration;

	//todo vedere nome, è lo stato in cui si colora e aspetta i figli
	int wait_counter;
	
    int launch_counter;
    int launch_baby;

    int moving_start_counter;			// counts the number of frames since moving started
    int moving_stop_counter;			// counts the number of frames since moving stopped
    //non penso che mi serve lo stop counter

    int script_duration;
    int script_counter;
    // textures
    QPixmap texture_swim[2];
    QPixmap texture_launch[2];
    QPixmap texture_death;		// e' sempre la stessa rovesciata

    QPoint pos_in;

    //@override non so se ha senso chiamarla virtual, pero' probabilmente serve anche per i bloober_babies
   // void Dir_Move() ; // mi serve
    void state();
	
    QPoint posBaby(int id);
	QPainterPath shape() const;

public:

    BlooberNanny(QPoint position,Direction direction = LEFT);
	
    //@override
    // @override setMoving() to add horizontal acceleration
    // pure virtual methods that must be implemented
    
    virtual std::string name() { return "Bloober_Nanny"; }
    virtual void animate();
    virtual void hit(Object* what, Direction fromDir);
    virtual void hurt();
    virtual void advance();
    bool isBlocked_up()   {return   blocked_up;}
    bool isBlocked_side() {return blocked_side;}

};
