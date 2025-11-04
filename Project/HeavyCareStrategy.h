/**
 * @file HeavyCareStrategy.h
 * @brief Declaration of the HeavyCareStrategy class.
 * This class implements the CareStrategy interface for plants requiring heavy care,
 * providing specific methods for watering, sunlight, and soil care.
 * @author Mosa Leiee
 * @date 26 October 2025
 */

#ifndef HEAVYCARESTRATEGY_H
#define HEAVYCARESTRATEGY_H

#include "CareStrategy.h"
/**
 * @class HeavyCareStrategy
 * @brief Concrete class implementing the CareStrategy for plants needing heavy care.
 * This class provides specific implementations for watering, sunlight, and soil care
 * tailored to plants that require more intensive care.
 */
class HeavyCareStrategy :public CareStrategy {


public:
	/**
	 * @brief Provides heavy watering to the plant.
	 * @param plant Pointer to the Plant object to be watered.
	 */
	void water(Plant* plant);
	/**
	 * @brief Provides lots of sunlight to the plant.
	 * @param plant Pointer to the Plant object to receive sunlight.
	 */
	void sunlight(Plant* plant);
	/**
	 * @brief Cares for the soil with nutrient-rich materials.
	 * @param plant Pointer to the Plant object whose soil is to be cared for.
	 */
	void soil(Plant* plant);
};

#endif
