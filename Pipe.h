#pragma once

#include "Inert.h"

class Pipe : public Inert
{
	
public:

	Pipe(QPoint position, std::string _level_name, int height = 1, std::string rotation = "");

	// pure virtual methods that must be implemented
	virtual std::string name();
	virtual void hit(Object* what, Direction fromDir);
};