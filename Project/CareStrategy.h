/**
 * @file CareStrategy.h
 * @brief Declaration of the CareStrategy abstract class.
 * This class defines the interface for different care strategies for plants,
 * including methods for watering, providing sunlight, and soil care.
 * @author Mosa Leiee
 * @date 26 October 2025
 */

#ifndef CARESTRATEGY_H
#define CARESTRATEGY_H


/**
 * @class CareStrategy
 * @brief Abstract class representing different care strategies for plants.
 * 
 * This class defines the interface for care strategies, including methods for watering,
 * providing sunlight, and soil care. Concrete implementations of this class will provide
 * specific care instructions based on the type of plant.
 */
class Plant;
class CareStrategy {


public:
	/**
	 * @brief Pure virtual function to water the plant.
	 * @param plant Pointer to the Plant object to be watered.
	 */
	virtual void water(Plant* plant) = 0;
	
	/**
	 * @brief Pure virtual function to provide sunlight to the plant.
	 * @param plant Pointer to the Plant object to receive sunlight.
	 */
	virtual void sunlight(Plant* plant) = 0;

	/**
	 * @brief Pure virtual function to care for the soil of the plant.
	 * @param plant Pointer to the Plant object whose soil is to be cared for.
	 */
	virtual void soil(Plant* plant) = 0;
};

#endif
#include "Plant.h"