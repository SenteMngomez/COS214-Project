/**
 * @file PlantFactory.h
 * @brief Factory for creating plants
 * @author Brayden
 * @date October 26, 2025
 */

#ifndef PLANTFACTORY_H
#define PLANTFACTORY_H

#include "Plant.h"
#include <string>
using namespace std;

class Plant;

/**
 * @class PlantFactory
 * @brief Factory class for plant creation
 * 
 * PlantFactory defines the interface for creating plants by type.
 * Concrete factories implement specific plant creation logic.
 */
class PlantFactory {

private:
	Plant* product;

protected:
	/**
     * @brief Set the product
     * @param p Pointer to the Plant to set as product
     */
	void setProduct(Plant* p){ 
		product = p; 
	}

public:
	PlantFactory() : product(nullptr) {}

	/**
     * @brief Create a plant of the specified type
     * @param type The type of plant to create (e.g., "Cactus")
     * @return Pointer to the created Plant
     */
	virtual Plant* createPlant(string type, string colour) = 0;

	/**
     * @brief Get the last created product
     * @return Pointer to the last created Plant
     */
	Plant* getProduct() const{ 
		return product; 
	}

	virtual ~PlantFactory()=default;
};

#endif
