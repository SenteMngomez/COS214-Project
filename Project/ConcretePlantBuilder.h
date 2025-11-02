#ifndef CONCRETE_PLANT_BUILDER_H
#define CONCRETE_PLANT_BUILDER_H

/**
 * @file ConcretePlantBuilder.h
 * @brief Concrete implementation of the PlantBuilder interface.
 *
 * Creates composite Plant objects such as PlantGroup, DecorativePot or
 * GiftWrapDecorator depending on the requested decorator type.
 *
 * @author Lesedi
 * @date October 30, 2025
 */

#include "PlantBuilder.h"
#include "PlantGroup.h"
#include "DecorativePot.h"
#include "GiftWrapDecorator.h"

/**
 * @class ConcretePlantBuilder
 * @brief Concrete builder that composes multiple Plant instances into a single
 *        composite Plant according to a decorator parameter.
 */
class ConcretePlantBuilder : public PlantBuilder {
public:
    /**
     * @brief Default constructor for ConcretePlantBuilder.
     */
    ConcretePlantBuilder() {};

    /**
     * @brief Build a composite plant using the provided plants and decorator.
     * @param plants Vector of Plant pointers to include in the composite
     * @param decorator String describing the decorator type (e.g., "wrap", "pot")
     * @return Plant* Newly constructed composite Plant
     */
    virtual Plant* buildCompositePlant(std::vector<Plant*> plants, std::string& decorator);
};

#endif //CONCRETE_PLANT_BUILDER_H