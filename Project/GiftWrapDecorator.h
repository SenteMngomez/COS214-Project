/**
 * @file GiftWrapDecorator.h
 * @brief Decorator for adding gift wrapping to plants
 * @author Brayden
 * @date October 26, 2025
 */

#ifndef GIFTWRAPDECORATOR_H
#define GIFTWRAPDECORATOR_H

#include "PlantDecorator.h"

/**
 * @class GiftWrapDecorator
 * @brief Decorator that adds gift wrapping to a plant
 * 
 * Wraps a plant for gifting/customization.
 */
class GiftWrapDecorator :public PlantDecorator {
private:
    string wrapType;

public:
	/**
     * @brief Construct a GiftWrapDecorator
     * @param plant Pointer to the plant
     * @param wrap The wrap type
     * @param colour Plant color
     * @param careStrategy Care strategy
     * @param price Plant price
     */
    GiftWrapDecorator(Plant* plant, string wrap, string colour, CareStrategy* careStrategy, double price);

	/**
     * @brief Print the plant with wrapping details
     */
	void print() override;
};

#endif
