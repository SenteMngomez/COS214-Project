#ifndef PLANT_BUILDER_H
#define PLANT_BUILDER_H

/**
 * @file PlantBuilder.h
 * @brief Abstract builder interface for composing Plant objects.
 *
 * PlantBuilder defines the interface for constructing composite Plant
 * instances (for example, groups wrapped in a decorative pot or gift wrap).
 * Concrete builders should implement buildCompositePlant to return a new
 * Plant pointer representing the composed product.
 *
 * @author Lesedi
 * @date October 30, 2025
 */

#include <vector>
#include <string>
#include "Plant.h"

/**
 * @class PlantBuilder
 * @brief Interface for building composite Plant objects.
 */
class PlantBuilder {
public:
    virtual ~PlantBuilder() = default;

    /**
     * @brief Build a composite Plant from a collection of plants.
     *
     * @param plants Vector of Plant pointers that form the composite product
     * @param decorator String indicating decorator type (e.g., "wrap", "pot").
     * @return Plant* Pointer to the newly constructed composite Plant.
     */
    virtual Plant* buildCompositePlant(std::vector<Plant*> plants, std::string& decorator) = 0;
};


#endif //PLANT_BUILDER_H