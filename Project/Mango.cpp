/**
 * @file Mango.cpp
 * @brief Implementation of Mango class
 * @author Brayden
 * @date October 26, 2025
 */

#include "Mango.h"

Mango::Mango(string colour, CareStrategy* careStrategy, double price)
    : Plant(colour, careStrategy, price) {}

Plant* Mango::clone() {
	return new Mango(*this);
}

void Mango::print() {
	cout << "Mango: " << getType() << ", Colour: " << getColour() << ", Price: R" << getPrice() << endl;
}

Plant* Mango::getChild(int tag){
	return nullptr;
}