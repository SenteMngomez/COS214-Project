/**
 * @file SucculentFactory.h
 * @brief Concrete factory for succulent plants
 * @author Brayden
 * @date October 26, 2025
 */

#ifndef SUCCULENTFACTORY_H
#define SUCCULENTFACTORY_H

#include "PlantFactory.h"
#include "Begonia.h"
#include "Cactus.h"

#include <string>
using namespace std;
class Plant;

/**
 * @class SucculentFactory
 * @brief Factory for creating succulent-type plants
 * 
 * Creates specific succulent plants like Begonias and Cacti.
 */
class SucculentFactory :public PlantFactory {

public:
	/**
     * @brief Create a succulent plant
     * @param type The succulent type
     * @return Pointer to the created plant
     */
	Plant* createPlant(string type);
};

#endif
