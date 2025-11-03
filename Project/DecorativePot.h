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

	/**
     * @brief Clone the decorated plant
     * @return Pointer to a cloned DecorativePot
     */
	Plant* clone() override;

	/**
     * @brief Get the type of the decorated plant
     * @return Type string with pot info
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
