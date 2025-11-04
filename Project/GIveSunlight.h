/**
 * @file GiveSunlight.h
 * @brief Command to give sunlight to plants in the greenhouse
 * @author Kundai
 * @date October 26, 2025
 */

#ifndef GIVESUNLIGHT_H
#define GIVESUNLIGHT_H

#include "Command.h"
class GiveSunlight :public Command {


public:
	/**
	 * @brief Construct a GiveSunlight command
	 */
	GiveSunlight();
	/**
	 * @brief Execute the GiveSunlight command on the specified plant IDs
	 * @param tags Vector of plant IDs to give sunlight to
	 * @param decorator Optional decorator string (not used in this command)
	 */
	virtual void execute(std::vector<string>* tags,string decorator="");
};

#endif
