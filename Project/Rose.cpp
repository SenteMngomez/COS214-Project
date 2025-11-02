/**
 * @file Rose.cpp
 * @brief Implementation of Rose class
 * @author Brayden
 * @date October 26, 2025
 */

#include "Rose.h"

Rose::Rose(string colour, CareStrategy* careStrategy, double price)
    : Plant(colour, careStrategy, price) {

		setTag(getType()+"#"+colour);
	}

Plant* Rose::clone() {
    return new Rose(*this);
}

void Rose::print() {
	cout << "Type: " << getType() << ", Colour: " << getColour() << ", Tag: " << getTag()  << ", Price: R" << getPrice() << endl;
}

Plant* Rose::getChild(string tag){
	return nullptr;
}
