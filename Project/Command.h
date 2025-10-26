#ifndef COMMAND_H
#define COMMAND_H


#include "Greenhouse.h"
#include "Inventory.h"
class Command {

protected:
	Greenhouse* greenHouse;
	Inventory* inventory;

public:
	virtual void execute(std::vector<int>* tag,string decorator="") = 0;
};

#endif
