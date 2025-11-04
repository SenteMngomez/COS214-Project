#include "ConcretePlantBuilder.h"

Plant* ConcretePlantBuilder::buildCompositePlant( vector<Plant*> plants , std::string& decorator){
        if (plants.empty()) return nullptr;

        Plant* result = nullptr;

        // If multiple plants, group them
        if (plants.size() > 1) {
            // Calculate total price of all plants
            double totalPrice = 0.0;
            for (auto* p : plants) {
                totalPrice += p->getPrice();
            }
            PlantGroup* group = new PlantGroup("Group", nullptr, totalPrice);
            for (auto* p : plants) {
                group->add(*p);  // PlantGroup takes ownership
            }
            result = group;
        } else {
            result = plants.front();
        }

        // Apply decorator if any
        if (decorator == "pot") {
            double decoratorPrice = 10.00; // Add cost for decorative pot
            result = new DecorativePot(result,decorator,result->getColour(),result->getCareStrategy(),result->getPrice() + decoratorPrice);
        } else if (decorator == "wrap") {
            double decoratorPrice = 6.00; // Add cost for gift wrap
            result = new GiftWrapDecorator(result, "Gift Wrap", result->getColour(), nullptr, result->getPrice() + decoratorPrice);
        }

        return result;
    }
