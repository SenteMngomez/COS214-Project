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
	Command();
	/**
	 * @brief Set the Greenhouse instance the command operates on.
	 * @param gh Pointer to the Greenhouse
	 */
	virtual void setGreenhouse(Greenhouse* gh);
	virtual void execute(vector<string>* tag,string decorator="") = 0;
};

#endif
