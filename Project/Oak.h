/**
 * @file Cactus.h
 * @brief Concrete Cactus plant class
 * @author Brayden
 * @date October 26, 2025
 */

#ifndef OAK_H
#define OAK_H
#include "Plant.h"

/**
 * @class Oak
 * @brief Concrete implementation of an Oak plant
 * 
 * Oak represents a sturdy tree plant with moderate care needs.
 * Implements cloning for Prototype pattern and basic operations.
 */

class Oak :public Plant {

public:
	/**
     * @brief Construct an Oak with colour, care strategy, and price
     * @param colour The colour of the oak
     * @param careStrategy Pointer to care strategy
     * @param price The price of the oak
     */
    Oak(string colour, CareStrategy* careStrategy, double price);

	/**
     * @brief Get the type of the plant
     * @return "Oak"
     */
    string getType() const override { return "Oak"; }

	/**
     * @brief Clone the oak
     * @return Pointer to a new Oak
     */
	Plant* clone();

	/**
     * @brief Print oak details
     */
	void print();

	// Composite methods (stubs for leaf plant)
    void add(Plant& plant) override {}
    void remove(Plant& plant) override {}
    void getChild(int tag) override {}
};

#endif
