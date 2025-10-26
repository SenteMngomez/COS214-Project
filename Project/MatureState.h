/**
 * @file MatureState.h
 * @brief Header file for the MatureState class, representing the mature state of a plant.
 * @author Mosa Leiee
 * @date 26 October 2025
 */
#ifndef MATURESTATE_H
#define MATURESTATE_H

#include "PlantState.h"
#include "Plant.h"
#include "DeadState.h"

/**
 * @class MatureState
 * @brief Represents the mature state of a plant.
 * This state handles the behavior of a plant that has fully grown and is now aging.
 * It requires normal care and will eventually transition to the dead state.
 */

class MatureState :public PlantState {


public:
	/**
	 * @brief Handle the state-specific behavior of the mature plant.
	 * @param plant Pointer to the Plant object whose state is being handled.
	 */
	void handle(Plant* plant);
};

#endif
