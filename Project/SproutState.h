/**
 * @file SproutState.h
 * @brief Header file for the SproutState class, representing the sprout state of a plant.
 * @author Mosa Leiee
 * @date 26 October 2025
 */

#ifndef SPROUTSTATE_H
#define SPROUTSTATE_H

#include "PlantState.h"
#include "Plant.h"
#include "MatureState.h"

/**
 * @class SproutState
 * @brief Represents the sprout state of a plant in its lifecycle.
 * This state handles the behavior and transitions specific to a sprout.
 */

class SproutState :public PlantState {


public:
	/**
	 * @brief Handle the state-specific behavior of the sprout.
	 * @param plant Pointer to the Plant object whose state is being handled.
	 */
	void handle(Plant* plant);
};

#endif
