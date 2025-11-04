/**
 * @file Tulip.h
 * @brief Concrete Tulip plant class
 * @author Brayden
 * @date October 26, 2025
 */

#ifndef TULIP_H
#define TULIP_H

#include "Plant.h"


class Tulip :public Plant {

/**
 * @class Tulip
 * @brief Concrete implementation of a Tulip plant
 * 
 * Tulip represents a bulbous flowering plant with moderate care needs.
 * Implements cloning for Prototype pattern and basic operations.
 */
public:
	/**
     * @brief Construct a Tulip with colour, care strategy, and price
     * @param colour The colour of the tulip
     * @param careStrategy Pointer to care strategy
     * @param price The price of the tulip
     */
    Tulip(string colour, CareStrategy* careStrategy, double price);

	/**
     * @brief Get the type of the plant
     * @return "Tulip"
     */
    string getType() const override { return "Tulip"; }

	/**
     * @brief Clone the tulip
     * @return Pointer to a new Tulip
     */
	Plant* clone();

	/**
     * @brief Print tulip details
     */
	void print();

	// Composite methods (stubs for leaf plant)
     /**
      * @brief Add a child plant (not applicable for leaf plants)
      * @param plant Reference to the plant to add
      */
    void add(Plant& plant) override {}
     /**
      * @brief Remove a child plant (not applicable for leaf plants)
      * @param plant Reference to the plant to remove
      */
    void remove(Plant& plant) override {}
     /**
      * @brief Get a child plant by tag (not applicable for leaf plants)
      * @param tag The tag of the child plant
      * @return Always returns nullptr for leaf plants
      */
    Plant* getChild(string tag) override;
};

#endif
