/**
 * @file DecorativePot.cpp
 * @brief Implementation of DecorativePot
 * @author Brayden
 * @date October 26, 2025
 */

#include "DecorativePot.h"

DecorativePot::DecorativePot(Plant* plant, string pot, string colour, CareStrategy* careStrategy, double price)
    : PlantDecorator(plant, colour, careStrategy, price), potType(pot) {}

void DecorativePot::print(){
	PlantDecorator::print();
    cout << "In " << potType << " pot." << endl;
}

Plant* DecorativePot::clone() {
    return new DecorativePot(component->clone(), potType, getColour(), nullptr, getPrice());
}

string DecorativePot::getType() const {
    return component->getType() + " in " + potType;
}

void DecorativePot::add(Plant& plant) {
    component->add(plant);
}

void DecorativePot::remove(Plant& plant) {
    component->remove(plant);
}

Plant* DecorativePot::getChild(int tag) {
    return component->getChild(tag);
}
