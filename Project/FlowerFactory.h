/**
 * @file FlowerFactory.h
 * @brief Concrete factory for flower plants
 * @author Brayden
 * @date October 26, 2025
 */

#ifndef FLOWERFACTORY_H
#define FLOWERFACTORY_H

#include "PlantFactory.h"
#include "Rose.h"
#include "Tulip.h"

#include <string>
class Plant;
using namespace std;

/**
 * @class FlowerFactory
 * @brief Factory for creating flower-type plants
 * 
 * Creates specific flower plants like Roses and Tulips.
 */
class FlowerFactory :public PlantFactory {

public:
	/**
     * @brief Create a flower plant
     * @param type The flower type
     * @return Pointer to the created plant
     */
	Plant* createPlant(string type);
};

#endif
