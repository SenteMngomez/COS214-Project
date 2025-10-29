#include "ConcretePlantBuilder.h"

Plant* ConcretePlantBuilder::buildCompositePlant(vector<Plant*> plants ,std::string& decorator){
        if (plants.empty()) return nullptr;

        Plant* result = nullptr;

        // If multiple plants, group them
        if (plants.size() > 1) {
            PlantGroup* group = new PlantGroup("Group", nullptr, 0.0);
            for (auto* p : plants) {
                group->add(*p);
            }
            result = group;
        } else {
            result = plants.front();
        }

        // Apply decorator if any
        if (decorator == "pot") {
            result = new DecorativePot(result,decorator,result->getColour(),result->getCareStrategy(),result->getPrice());
        } else if (decorator == "wrap") {
            result = new GiftWrapDecorator(result, "Gift Wrap", result->getColour(), nullptr, result->getPrice());
        }

        return result;
    }
