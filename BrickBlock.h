#pragma once
#include "KoopaTroopa.h"
#include "BouncingBlock.h"
#include "BrokenBlock.h"
class BrickBlock : public BouncingBlock
{
protected:
	std::string type;
	QPixmap texture_active[4];
	QPixmap texture_inactive[2];
	/*BrokenBlock* fragments[2][2];*/
public:

	BrickBlock(QPoint position, std::string _type);

	virtual std::string name() { return "BrickBlock"; }
	virtual void advance();
	virtual void animate();
	virtual void hit(Object* what, Direction fromDir);
};