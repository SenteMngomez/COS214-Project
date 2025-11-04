/**
 * @file Rose.h
 * @brief Concrete Rose plant class
 * @author Brayden
 * @date October 26, 2025
 */

#ifndef ROSE_H
#define ROSE_H

#include "Plant.h"

/**
 * @class Rose
 * @brief Concrete implementation of a Rose plant
 * 
 * Rose represents a classic flowering plant with standard care needs.
 * Implements cloning for Prototype pattern and basic operations.
 */
class Rose :public Plant {


public:

	/**
     * @brief Construct a Rose with colour, care strategy, and price
     * @param colour The colour of the rose
     * @param careStrategy Pointer to care strategy
     * @param price The price of the rose
     */
    Rose(string colour, CareStrategy* careStrategy, double price);

	/**
     * @brief Get the type of the plant
     * @return "Rose"
     */
    string getType() const override { return "Rose"; }

	/**
     * @brief Clone the rose
     * @return Pointer to a new Rose
     */
	Plant* clone();

	/**
     * @brief Print rose details
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
      * @return nullptr since leaf plants have no children
      */
    Plant* getChild(string tag) override;
};

#endif
