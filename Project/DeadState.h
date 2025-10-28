/**
 * @file DeadState.h
 * @brief Header file for the DeadState class, representing the dead state of a plant.
 * @author Mosa Leiee
 * @date 26 October 2025
 */
#ifndef DEADSTATE_H
#define DEADSTATE_H

#include "PlantState.h"
#include "Plant.h"

/**
 * @class DeadState
 * @brief Represents the dead state of a plant in the state pattern.
 * In this state, the plant can no longer grow or respond to care.
 */

class DeadState :public PlantState {


public:
	/**
	 * @brief Handle the state-specific behavior of the plant when it is dead.
	 * @param plant Pointer to the Plant object whose state is being handled.
	 */
	void handle(Plant* plant);
};

#endif
