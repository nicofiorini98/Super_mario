#pragma once
#include "Enemy.h"
#include "BabyCheep.h"
#include "Mario.h"

class BigBertha : public Enemy
{
private:
    Mario* mario;
    bool launch_baby;                //is big bertha launch the baby during the script?
	
    int moving_start_counter;        //counts the number of frames since the script is started
    int stopped_start_counter;       //counts the number of frames since big bertha is stopped
    int script_counter;              //counts the number of pixel moved since the script is started
    int script_duration;             //limit on the number of pixels to move

protected:
    // textures
    QPixmap texture_swim_open[2];
    QPixmap texture_swim_close[2];
    QPixmap texture_death;		
    BabyCheep* baby;

public:

    BigBertha(QPoint position, Direction direction = LEFT);
	
    // pure virtual methods that must be implemented
    virtual std::string name() { return "BigBertha"; }
    virtual void animate();
    virtual void hit(Object* what, Direction fromDir);
    virtual void hurt();
    virtual void advance();
    QPainterPath shape() const;

};