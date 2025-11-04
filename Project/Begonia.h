/**
 * @file Begonia.h
 * @brief Concrete Begonia plant class
 * @author Brayden
 * @date October 26, 2025
 */

#ifndef BEGONIA_H
#define BEGONIA_H

#include "Plant.h"

/**
 * @class Begonia
 * @brief Concrete implementation of a Begonia plant
 * 
 * Begonia represents a flowering plant with moderate care needs.
 * Implements cloning for Prototype pattern and basic operations.
 */
class Begonia :public Plant {


public:

	/**
     * @brief Construct a Begonia with colour, care strategy, and price
     * @param colour The colour of the begonia
     * @param careStrategy Pointer to care strategy
     * @param price The price of the begonia
     */
    Begonia(string colour, CareStrategy* careStrategy, double price);

	/**
     * @brief Get the type of the plant
     * @return "Begonia"
     */
    string getType() const override { return "Begonia"; }

	/**
     * @brief Clone the begonia
     * @return Pointer to a new Begonia
     */
	Plant* clone();

	/**
     * @brief Print begonia details
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
     */
    Plant* getChild(string tag) override;
};

#endif
