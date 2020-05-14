#pragma once

#include "Inert.h"

class FixedBlock : public Inert
{
	public:

		FixedBlock(QPoint pos ,std::string _type);

		// pure virtual methods that must be implemented
		virtual std::string name() { return "Block"; }
		virtual void hit(Object* what, Direction fromDir) { /* do nothing */ }
};