/**
 * @file LightCareStrategy.h
 * @brief Declaration of the LightCareStrategy class.
 * This class implements the CareStrategy interface for plants requiring light care,
 * providing specific methods for watering, sunlight, and soil care.
 * @author Mosa Leiee
 * @date 26 October 2025
 */

#ifndef LIGHTCARESTRATEGY_H
#define LIGHTCARESTRATEGY_H

#include "CareStrategy.h"
/**
 * @class LightCareStrategy
 * @brief Concrete class implementing the CareStrategy for plants needing light care.
 * This class provides specific implementations for watering, sunlight, and soil care
 * tailored to plants that require minimal care.
 */
class LightCareStrategy :public CareStrategy {


public:
	/**
	 * @brief Provides light watering to the plant.
	 * @param plant Pointer to the Plant object to be watered.
	 */
	void water(Plant* plant);
	/**
	 * @brief Provides limited sunlight to the plant.
	 * @param plant Pointer to the Plant object to receive sunlight.
	 */
	void sunlight(Plant* plant);
	/**
	 * @brief Cares for the soil with well-drained materials.
	 * @param plant Pointer to the Plant object whose soil is to be cared for.
	 */
	void soil(Plant* plant);
};

#endif
