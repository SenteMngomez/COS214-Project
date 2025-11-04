/**
 * @file PlantDecorator.cpp
 * @brief Implementation of PlantDecorator
 * @author Brayden
 * @date October 26, 2025
 */

#include "PlantDecorator.h"

PlantDecorator::PlantDecorator(Plant* plant, string colour, CareStrategy* careStrategy, double price)
    : Plant(colour, careStrategy, price), component(plant) {}

PlantDecorator::~PlantDecorator() {
    delete component;  // Delete the wrapped plant
}

void PlantDecorator::print(){
	if(component){
        component->print();
    }
    cout << " (Decorated)" << endl;
}
