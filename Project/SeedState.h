/**
 * @file SeedState.h
 * @brief Header file for the SeedState class representing the seed stage of a plant.
 * @author Mosa Leiee
 * @date 26 October 2025
 */
#ifndef SEEDSTATE_H
#define SEEDSTATE_H

#include "PlantState.h"
#include "SproutState.h"

/**
 * @class SeedState
 * @brief Represents the seed stage of a plant in its lifecycle.
 * This state handles the transition from seed to sprout.
 */

class SeedState :public PlantState {


public:
	/**
	 * @brief Handle the seed state behavior of the plant.
	 * @param plant Pointer to the Plant object whose state is being handled.
	 */
	void handle(Plant* plant);

	/**
	 * @brief Returns the name of the state
	 */
	virtual std::string getType();
};

#endif
