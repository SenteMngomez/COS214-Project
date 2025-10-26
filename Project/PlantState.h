/**
 * @file PlantState.h
 * @brief Abstract base class for plant states in the State design pattern.
 * This class defines the interface for handling state-specific behavior of plants.
 * Each concrete state class will implement the handle method to define
 * how the plant behaves in that particular state.
 * @author Mosa Leiee
 * @date 26 October 2025
 */

#ifndef PLANTSTATE_H
#define PLANTSTATE_H
#include "Plant.h"

/**
 * @class PlantState
 * @brief Abstract base class for plant states.
 * This class defines the interface for handling state-specific behavior of plants.
 * Each concrete state class will implement the handle method to define
 * how the plant behaves in that particular state.
 */
class PlantState {


public:
	/**
	 * @brief Handle the state-specific behavior of the plant.	
	 * @param plant Pointer to the Plant object whose state is being handled.
	 */
	virtual void handle(Plant* plant) = 0;
	/**
	 * @brief Virtual destructor for PlantState.s
	 */
	virtual ~PlantState(){}
};

#endif
