#include "ConcretePlantBuilder.h"

Plant* ConcretePlantBuilder::buildCompositePlant(vector<Plant*> plants ,std::string decorator){
        if (plants.empty()) return nullptr;

        Plant* result = nullptr;

        // If multiple plants, group them
        if (plants.size() > 1) {
            PlantGroup* group = new PlantGroup();
            for (auto* p : plants) {
                group->add(p);
            }
            result = group;
        } else {
            result = plants.front();
        }

        // Apply decorator if any
        if (decorator == "pot") {
            result = new DecorativePot(result);
        } else if (decorator == "wrap") {
            result = new GiftWrapDecorator(result);
        }

        return result;
    }
