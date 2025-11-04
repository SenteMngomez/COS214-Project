/**
 * @file PlantDecorator.h
 * @brief Base decorator for plant customizations
 * @author Brayden
 * @date October 26, 2025
 */

#ifndef PLANTDECORATOR_H
#define PLANTDECORATOR_H

#include "Plant.h"
#include <iostream>

/**
 * @class PlantDecorator
 * @brief Base class for decorating plants with additional features
 * 
 * PlantDecorator wraps a Plant to add customizations like pots or wrapping
 * without modifying the core Plant class.
 */
class PlantDecorator :public Plant {
protected:
     /// @brief The wrapped plant component
	Plant* component;

public:
	/**
     * @brief Construct a decorator around a plant
     * @param plant Pointer to the plant to decorate
     * @param colour Inherited color
     * @param careStrategy Inherited care strategy
     * @param price Inherited price
     */
	PlantDecorator(Plant* plant, string colour, CareStrategy* careStrategy, double price);

	/**
     * @brief Destructor - cleans up the wrapped component
     */
	virtual ~PlantDecorator();	/**
     * @brief Print the decorated plant
     */
	void print() override;
};

#endif
