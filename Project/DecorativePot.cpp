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
