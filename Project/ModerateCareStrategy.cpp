/**
 * @file ModerateCareStrategy.cpp
 * @brief Implementation of the ModerateCareStrategy class.
 * This class provides specific care instructions for plants requiring moderate care,
 * including methods for watering, sunlight, and soil care.
 * @author Mosa Leiee
 * @date 26 October 2025
 */

#include "ModerateCareStrategy.h"
#include <iostream>
using namespace std;

/**
 * @brief Provides moderate watering to the plant.
 * @param plant Pointer to the Plant object to be watered.
 */
void ModerateCareStrategy::water(Plant* plant) {

	cout<<"Giving the plant 150ml of water."<<endl;
}

/**
 * @brief Provides adequate sunlight to the plant.
 * @param plant Pointer to the Plant object to receive sunlight.
 */
void ModerateCareStrategy::sunlight(Plant* plant){

	cout<<"Placing the plant in indirect sunlight for 6-8 hours."<<endl;
}

/**
 * @brief Cares for the soil with standard materials.
 * @param plant Pointer to the Plant object whose soil is to be cared for.
 */
void ModerateCareStrategy::soil(Plant* plant) {

	cout<<"Using our standard potting soil."<<endl;
}
