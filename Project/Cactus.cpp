/**
 * @file Cactus.cpp
 * @brief Implementation of Cactus class
 * @author Brayden
 * @date October 26, 2025
 */

#include "Cactus.h"

Cactus::Cactus(string colour, CareStrategy* careStrategy, double price)
    : Plant(colour, careStrategy, price) {
		setTag(getType()+"#"+colour);
	}

Plant* Cactus::clone() {
	return new Cactus(*this);
}

void Cactus::print() {
	cout << "Type: " << getType() << ", Colour: " << getColour() << ", Tag: " << getTag() << ", Price: R" << getPrice() << endl;
}

Plant* Cactus::getChild(string tag){
	return nullptr;
}