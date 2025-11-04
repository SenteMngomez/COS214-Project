/**
 * @file GiftWrapDecorator.cpp
 * @brief Implementation of GiftWrapDecorator
 * @author Brayden
 * @date October 26, 2025
 */

#include "GiftWrapDecorator.h"

GiftWrapDecorator::GiftWrapDecorator(Plant* plant, string wrap, string colour, CareStrategy* careStrategy, double price)
    : PlantDecorator(plant, colour, careStrategy, price), wrapType(wrap) {}

void GiftWrapDecorator::print(){
    PlantDecorator::print();
    cout << "Wrapped with " << wrapType << "." << endl;
}

Plant* GiftWrapDecorator::clone() {
    return new GiftWrapDecorator(component->clone(), wrapType, getColour(), nullptr, getPrice());
}

string GiftWrapDecorator::getType() const {
    return component->getType() + " with " + wrapType;
}

void GiftWrapDecorator::add(Plant& plant) {
    component->add(plant);
}

void GiftWrapDecorator::remove(Plant& plant) {
    component->remove(plant);
}

Plant* GiftWrapDecorator::getChild(std::string tag) {
    return component->getChild(tag);
}
