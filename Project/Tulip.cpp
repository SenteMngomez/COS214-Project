/**
 * @file Tulip.cpp
 * @brief Implementation of Tulip class
 * @author Brayden
 * @date October 26, 2025
 */

#include "Tulip.h"

Tulip::Tulip(string colour, CareStrategy* careStrategy, double price)
    : Plant(colour, careStrategy, price) {}

Plant* Tulip::clone() {
    return new Tulip(*this);
}

void Tulip::print() {
	cout << "Type: " << getType() << ", Colour: " << getColour() << ", Tag: " << getTag()  << ", Price: R" << getPrice() << endl;
}

Plant* Tulip::getChild(int tag){
	return nullptr;
}
