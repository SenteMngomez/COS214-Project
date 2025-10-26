/**
 * @file DecorativePot.h
 * @brief Decorator for adding a decorative pot to plants
 * @author Brayden
 * @date October 26, 2025
 */

#ifndef DECORATIVEPOT_H
#define DECORATIVEPOT_H

#include "PlantDecorator.h"

/**
 * @class DecorativePot
 * @brief Decorator that adds a decorative pot to a plant
 * 
 * Enhances a plant with a pot for sales/customization.
 */
class DecorativePot :public PlantDecorator {
private:
	string potType;

public:
	/**
     * @brief Construct a DecorativePot decorator
     * @param plant Pointer to the plant
     * @param pot The pot type
     * @param colour Plant colour
     * @param careStrategy Care strategy
     * @param price Plant price
     */
    DecorativePot(Plant* plant, string pot, string colour, CareStrategy* careStrategy, double price);

	/**
     * @brief Print the plant with pot details
     */
	void print() override;
};

#endif
