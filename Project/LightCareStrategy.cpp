/**
 * @file LightCareStrategy.cpp
 * @brief Implementation of the LightCareStrategy class.
 * This class provides specific care instructions for plants requiring light care,
 * including methods for watering, sunlight, and soil care.
 * @author Mosa Leiee
 * @date 26 October 2025
 */

#include "LightCareStrategy.h"
#include <iostream>
using namespace std;

/**
 * @brief Provides light watering to the plant.
 * @param plant Pointer to the Plant object to be watered.
 */
void LightCareStrategy::water(Plant* plant) {

	cout<<"Giving the "<< plant->getType() << " 100ml of water."<<endl;
}

/**
 * @brief Provides limited sunlight to the plant.
 * @param plant Pointer to the Plant object to receive sunlight.
 */
void LightCareStrategy::sunlight(Plant* plant) {

	cout<<"Placing the "<< plant->getType() <<" in partial sunlight for 3-4 hours."<<endl;
}

/**
 * @brief Cares for the soil with well-drained materials.
 * @param plant Pointer to the Plant object whose soil is to be cared for.
 */
void LightCareStrategy::soil(Plant* plant) {

	cout<<"Using sandy or well-drained soil for the " <<plant->getType()<<endl;
}