/**
 * @file HeavyCareStrategy.cpp
 * @brief Implementation of the HeavyCareStrategy class.
 * This class provides specific care instructions for plants requiring heavy care,
 * including methods for watering, sunlight, and soil care.
 * @author Mosa Leiee
 * @date 26 October 2025
 */

#include "HeavyCareStrategy.h"
#include <iostream>
using namespace std;

/**
 * @brief Provides heavy watering to the plant.
 * @param plant Pointer to the Plant object to be watered.
 */
void HeavyCareStrategy::water(Plant* plant) {
	
	cout<<"Giving the "<< plant->getType() <<" 300-350ml of water."<<endl;
}

/**
 * @brief Provides lots of sunlight to the plant.
 * @param plant Pointer to the Plant object to receive sunlight.
 */
void HeavyCareStrategy::sunlight(Plant* plant) {

	cout<<"Placing the "<< plant->getType() <<" in direct sunlight for 6-9 hours."<<endl;
}

/**
 * @brief Cares for the soil with nutrient-rich materials.
 * @param plant Pointer to the Plant object whose soil is to be cared for.
 */
void HeavyCareStrategy::soil(Plant* plant) {

	cout<<"Enriching the "<<plant->getType()<<"'s soil with nutrient-rich, moist soil."<<endl;
}