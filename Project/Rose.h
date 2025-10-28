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
    void add(Plant& plant) override {}
    void remove(Plant& plant) override {}
    Plant* getChild(int tag) override;
};

#endif
