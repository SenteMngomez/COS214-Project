/**
 * @file Mango.h
 * @brief Concrete Mango plant class
 * @author Brayden
 * @date October 26, 2025
 */

#ifndef MANGO_H
#define MANGO_H

#include "Plant.h"

/**
 * @class Mango
 * @brief Concrete implementation of a Mango plant
 * 
 * Mango represents a fruit-bearing tree plant with heavy care needs.
 * Implements cloning for Prototype pattern and basic operations.
 */
class Mango :public Plant {

public:
	/**
     * @brief Construct a Mango with colour, care strategy, and price
     * @param colour The colour of the mango
     * @param careStrategy Pointer to care strategy
     * @param price The price of the mango
     */
    Mango(string colour, CareStrategy* careStrategy, double price);

	/**
     * @brief Get the type of the plant
     * @return "Mango"
     */
    string getType() const override { return "Mango"; }

	/**
     * @brief Clone the mango
     * @return Pointer to a new Mango
     */
	Plant* clone();

	/**
     * @brief Print mango details
     */
	void print();

	// Composite methods (stubs for leaf plant)
    void add(Plant& plant) override {}
    void remove(Plant& plant) override {}
    Plant* getChild(int tag) override;
};

#endif
