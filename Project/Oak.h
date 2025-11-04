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
      * @return nullptr as leaf plants do not have children
      */
    Plant* getChild(string tag) override;
};

#endif
