#pragma once
#include "KoopaTroopa.h"
#include "BouncingBlock.h"
#include "BrokenBlock.h"
class BrickBlock : public BouncingBlock
{
protected:
	std::string type;                       //is ice or normal?
	QPixmap texture_active[4];              //breakable block texture
	QPixmap texture_inactive[2];            //unbreakable block texture
	
public:

	BrickBlock(QPoint position, std::string _type);

	virtual std::string name() { return "BrickBlock"; }
	virtual void advance();
	virtual void animate();
	virtual void hit(Object* what, Direction fromDir);
};