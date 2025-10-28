/**
 * @file Begonia.cpp
 * @brief Implementation of Begonia class
 * @author Brayden
 * @date October 26, 2025
 */

#include "Begonia.h"

Begonia::Begonia(string colour, CareStrategy* careStrategy, double price)
    : Plant(colour, careStrategy, price) {}

Plant* Begonia::clone() {
	return new Begonia(*this);;
}

void Begonia::print() {
	cout << "Begonia: " << getType() << ", Colour: " << getColour() << ", Price: R" << getPrice() << endl;
}
