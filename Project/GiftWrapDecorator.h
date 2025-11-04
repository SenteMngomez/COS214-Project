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

     /// @brief Type of the gift wrap
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

	/**
     * @brief Clone the decorated plant
     * @return Pointer to a cloned GiftWrapDecorator
     */
	Plant* clone() override;

	/**
     * @brief Get the type of the decorated plant
     * @return Type string with wrapping info
     */
	string getType() const override;

	/**
     * @brief Add a child plant (delegates to component if applicable)
     * @param plant Reference to the plant to add
     */
	void add(Plant& plant) override;

	/**
     * @brief Remove a child plant (delegates to component if applicable)
     * @param plant Reference to the plant to remove
     */
	void remove(Plant& plant) override;

	/**
     * @brief Get a child plant by tag (delegates to component)
     * @param tag The tag of the child plant
     * @return Pointer to the child plant, or nullptr
     */
	Plant* getChild(std::string tag) override;
};

#endif
