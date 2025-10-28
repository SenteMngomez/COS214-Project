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
