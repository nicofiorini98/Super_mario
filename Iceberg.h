#pragma once

#include "Inert.h"

class Iceberg : public Inert
{
private:
	std::string _type;  // iceberg's type...
public:
	Iceberg(QRect rect, std::string _level_name, std::string _type,std::string pos_rel_to_water_lvl = "");

	// getters 
	std::string type() { return _type; }

	// pure virtual methods that must be implemented
	virtual std::string name();
	virtual void hit(Object* what, Direction fromDir) { /* do nothing */ }
};