/**
 * @file Rose.cpp
 * @brief Implementation of Rose class
 * @author Brayden
 * @date October 26, 2025
 */

#include "Rose.h"

Rose::Rose(string colour, CareStrategy* careStrategy, double price)
    : Plant(colour, careStrategy, price) {}

Plant* Rose::clone() {
    return new Rose(*this);
}

void Rose::print() {
	cout << "Rose: " << getType() << ", Colour: " << getColour() << ", Price: R" << getPrice() << endl;
}
