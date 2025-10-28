#ifndef PLANT_BUILDER_H
#define PLANT_BUILDER_H

#include <vector>
#include <string>
#include "Plant.h"

class PlantBuilder {
public:
    virtual ~PlantBuilder() = default;

    virtual Plant* buildCompositePlant(const std::vector<Plant*>& plants, const std::string& decorator) = 0;
};


#endif //PLANT_BUILDER_H