#pragma once
#include "Enemy.h"
#include "BabyCheep.h"
#include "Mario.h"

class BigBertha : public Enemy
{
private:
    bool launch_baby;          //quando è attivo, si attiva lo script e mi deve lanciare la creatura
    int moving_start_counter;  //moving start counter forse meglio metterlo in enemy visto che serve a tutti i nemici
    int script_counter;
    int blocked_counter;
    int script_duration;
    int count_script = 0;  // è momentaneo
    Mario* mario;
    void state();

protected:
    // textures
    QPixmap texture_swim_open[2];
    QPixmap texture_swim_close[2];
    QPixmap texture_death;		// brown/red smashed texture
    BabyCheep* baby;

public:

    BigBertha(QPoint position, Direction direction = LEFT);
    // pure virtual methods that must be implemented
    virtual std::string name() { return "Big_Bertha"; }
    virtual void animate();
    virtual void hit(Object* what, Direction fromDir);
    virtual void hurt();
    virtual void advance();

};