/**
 * @file Mango.cpp
 * @brief Implementation of Mango class
 * @author Brayden
 * @date October 26, 2025
 */

#include "Mango.h"

Mango::Mango(string colour, CareStrategy* careStrategy, double price)
    : Plant(colour, careStrategy, price) {

		setTag(getType()+"#"+colour);
	}

Plant* Mango::clone() {
	return new Mango(*this);
}

void Mango::print() {
	cout << "Type: " << getType() << ", Colour: " << getColour() << ", Tag: " << getTag()  << ", Price: R" << getPrice() << endl;
}

Plant* Mango::getChild(string tag){
	return nullptr;
}