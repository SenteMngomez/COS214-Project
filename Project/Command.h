#ifndef COMMAND_H
#define COMMAND_H


#include "Greenhouse.h"
#include "Inventory.h"
#include <vector>
class Command {

protected:

	/// @brief Pointer to the Greenhouse instance
	Greenhouse* greenHouse;
	/// @brief Pointer to the Inventory instance
	Inventory* inventory;

public:
	/**
	 * @brief Constructor for Command
	 */
	Command();
	/**
	 * @brief Set the Greenhouse instance the command operates on.
	 * @param gh Pointer to the Greenhouse
	 */
	virtual void setGreenhouse(Greenhouse* gh);
	/**
	 * @brief Set the Inventory instance the command operates on.
	 * @param inv Pointer to the Inventory
	 */
	virtual void execute(vector<string>* tag,string decorator="") = 0;
};

#endif
