/**
 * @file TreeFactory.h
 * @brief Concrete factory for tree plants
 * @author Brayden
 * @date October 26, 2025
 */

#ifndef TREEFACTORY_H
#define TREEFACTORY_H

#include "PlantFactory.h"
#include "Mango.h"
#include "Oak.h"

#include <string>
using namespace std;
class Plant;

/**
 * @class TreeFactory
 * @brief Factory for creating tree-type plants
 * 
 * Creates specific tree plants like Mangoes and Oaks.
 */
class TreeFactory :public PlantFactory {

public:
	/**
     * @brief Create a tree plant
     * @param type The tree type
     * @return Pointer to the created plant
     */
	Plant* createPlant(string type);
};

#endif
