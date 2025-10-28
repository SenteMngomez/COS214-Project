#ifndef CONCRETE_PLANT_BUILDER_H
#define CONCRETE_PLANT_BUILDER_H


#include "PlantBuilder.h"
#include "PlantGroup.h"
#include "DecorativePot.h"
#include "GiftWrapDecorator.h"

class ConcretePlantBuilder : public PlantBuilder {
public:
    Plant* buildCompositePlant(std::vector<Plant*> plants, std::string& decorator) ;
};

#endif //CONCRETE_PLANT_BUILDER_H 