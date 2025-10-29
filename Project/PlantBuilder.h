#ifndef PLANT_BUILDER_H
#define PLANT_BUILDER_H

#include <vector>
#include <string>
#include "Plant.h"

class PlantBuilder {
public:
    virtual ~PlantBuilder() = default;

    virtual Plant* buildCompositePlant(std::vector<Plant*> plants,std::string& decorator) = 0;
};


#endif //PLANT_BUILDER_H