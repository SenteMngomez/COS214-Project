#ifndef COMMAND_H
#define COMMAND_H


#include "Greenhouse.h"
#include "Inventory.h"
#include <vector>
class Command {

protected:
	Greenhouse* greenHouse;
	Inventory* inventory;

public:
	virtual void setGreenhouse(Greenhouse* gh)=0;
	virtual void execute(vector<int>* tag,string decorator="") = 0;
};

#endif
