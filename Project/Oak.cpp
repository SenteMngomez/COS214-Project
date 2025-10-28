/**
 * @file Oak.cpp
 * @brief Implementation of Oak class
 * @author Brayden
 * @date October 26, 2025
 */

#include "Oak.h"

Oak::Oak(string colour, CareStrategy* careStrategy, double price)
    : Plant(colour, careStrategy, price) {}

Plant* Oak::clone() {
	return new Oak(*this);
}

void Oak::print() {
	 cout << "Oak: " << getType() << ", Colour: " << getColour() << ", Price: R" << getPrice() << endl;
}

Plant* Oak::getChild(int tag){
	return nullptr;
}