/**
 * @file Cactus.h
 * @brief Concrete Cactus plant class
 * @author Brayden
 * @date October 26, 2025
 */

#ifndef CACTUS_H
#define CACTUS_H

#include "Plant.h"
#include <iostream>
using namespace std;

/**
 * @class Cactus
 * @brief Concrete implementation of a Cactus plant
 * 
 * Cactus represents a drought-tolerant plant with light care needs.
 * Implements cloning for Prototype pattern and basic operations.
 */
class Cactus :public Plant {

public:

	/**
     * @brief Construct a Cactus with colour, care strategy, and price
     * @param colour The colour of the cactus
     * @param careStrategy Pointer to care strategy
     * @param price The price of the cactus
     */
    Cactus(string colour, CareStrategy* careStrategy, double price);

	/**
     * @brief Get the type of the plant
     * @return "Cactus"
     */
    string getType() const override { return "Cactus"; }

	/**
     * @brief Clone the cactus
     * @return Pointer to a new Cactus
     */
	Plant* clone();

	/**
     * @brief Print cactus details
     */
	void print();

	// Composite methods (stubs for leaf plant)
    void add(Plant& plant) override {}
    void remove(Plant& plant) override {}
    Plant* getChild(string tag) override;
};

#endif
