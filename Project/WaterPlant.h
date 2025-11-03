#ifndef WATERPLANT_H
#define WATERPLANT_H

/**
 * @file WaterPlant.h
 * @brief Command to water plants identified by tag(s).
 *
 * Implements the Command interface for watering plants. The command may
 * operate on one or more plant tags and optionally accept a decorator
 * parameter (kept for API compatibility with other commands).
 *
 * @author Lesedi
 * @date October 30, 2025
 */

#include "Command.h"

/**
 * @class WaterPlant
 * @brief Concrete Command that waters plant(s) in the greenhouse.
 *
 * Derived from the Command base class. Calling execute will perform the
 * watering action for the supplied plant tag list.
 */
class WaterPlant : public Command {

public:
	/**
	 * @brief Construct a new WaterPlant command.
	 */
	WaterPlant();

	/**
	 * @brief Execute the watering command.
	 *
	 * @param tag Pointer to a vector of plant tag ids to act on. May be nullptr
	 *            or empty depending on caller.
	 * @param decorator Optional decorator string (not used by watering but
	 *                  provided for API consistency).
	 */
	virtual void execute(vector<string>* tag, string decorator = "");
};

#endif
