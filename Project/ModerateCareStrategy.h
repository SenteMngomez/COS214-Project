/**
 * @file ModerateCareStrategy.h
 * @brief Declaration of the ModerateCareStrategy class.
 * This class implements the CareStrategy interface for plants requiring moderate care,
 * providing specific methods for watering, sunlight, and soil care.
 * @author Mosa Leiee
 * @date 26 October 2025
 */

#ifndef MODERATECARESTRATEGY_H
#define MODERATECARESTRATEGY_H

#include "CareStrategy.h"
/**
 * @class ModerateCareStrategy
 * @brief Concrete class implementing the CareStrategy for plants needing moderate care.
 * This class provides specific implementations for watering, sunlight, and soil care
 * tailored to plants that require balanced care.
 */
class ModerateCareStrategy :public CareStrategy {


public:
	/**
	 * @brief Provides moderate watering to the plant.
	 * @param plant Pointer to the Plant object to be watered.
	 */
	void water(Plant* plant);
	/**
	 * @brief Provides adequate sunlight to the plant.
	 * @param plant Pointer to the Plant object to receive sunlight.
	 */
	void sunlight(Plant* plant);
	/**
	 * @brief Cares for the soil with standard materials.
	 * @param plant Pointer to the Plant object whose soil is to be cared for.
	 */
	void soil(Plant* plant);
};

#endif
